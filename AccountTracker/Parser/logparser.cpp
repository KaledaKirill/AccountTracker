#include "LogParser.h"

QMap<QString, QList<QDate>> LogParser::parseFileLog(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Unable to open file.");
        return QMap<QString, QList<QDate>>();
    }

    QTextStream in(&file);
    QString logText = in.readAll();
    file.close();

    return extractInviteDates(logText);
}

QMap<QString, QList<QDate>> LogParser::parseLogText(const QString& logText) {
    return extractInviteDates(logText);
}

QMap<QString, QList<QDate>> LogParser::extractInviteDates(const QString& logText) {
    QMap<QString, QList<QDate>> logData;
    QStringList lines = logText.split('\n');
    QRegularExpression regex(R"(\[([^\]]+)\] \[➕Инвайт\] tdata_(\d+)\.session -> \w+ \| Пользователь успешно добавлен)");

    for (const QString& line : lines) {
        QRegularExpressionMatch match = regex.match(line);

        if (match.hasMatch()) {
            QString accountId = match.captured(2);
            QString dateStr = match.captured(1);
            QDateTime dateTime = QDateTime::fromString(dateStr, "dd.MM.yyyy hh:mm:ss");

            if (dateTime.isValid()) {
                QDate date = dateTime.date();
                if (logData.contains(accountId)) {
                    logData[accountId].append(date);
                } else {
                    logData[accountId] = {date};
                }
            } else {
                qWarning() << "Invalid date format:" << dateStr;
            }
        }
    }

    return logData;
}
