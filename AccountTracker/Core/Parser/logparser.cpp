#include "LogParser.h"

QMap<QString, QList<QDateTime>> LogParser::parseFileLog(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning("Unable to open file.");
        _log.warning(__FILE__, "Unable to open file: " + filePath);
        return QMap<QString, QList<QDateTime>>();
    }

    QTextStream in(&file);
    QString logText = in.readAll();
    file.close();

    return extractInviteDates(logText);
}

QMap<QString, QList<QDateTime>> LogParser::parseLogText(const QString& logText)
{
    return extractInviteDates(logText);
}

QMap<QString, QList<QDateTime>> LogParser::extractInviteDates(const QString& logText)
{
    QMap<QString, QList<QDateTime>> logData;
    QStringList lines = logText.split('\n');
    QRegularExpression regex(R"(\[([^\]]+)\] \[➕Инвайт\] tdata_(\d+)\.session -> \w+ \| Пользователь успешно добавлен)");

    for (const QString& line : lines)
    {
        QRegularExpressionMatch match = regex.match(line);

        if (match.hasMatch())
        {
            QString accountId = match.captured(2);
            QString dateStr = match.captured(1);
            QDateTime dateTime = QDateTime::fromString(dateStr, "dd.MM.yyyy hh:mm:ss");

            if (dateTime.isValid())
            {
                if (logData.contains(accountId))
                    logData[accountId].append(dateTime);
                else
                    logData[accountId] = {dateTime};
            }
            else
                _log.warning(__FILE__, "Invalid date format:" + dateStr);
        }
    }

    return logData;
}
