#ifndef LOGPARSER_H
#define LOGPARSER_H

#include "ILogParser.h"
#include <QString>
#include <QMap>
#include <QList>
#include <QDate>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

class LogParser : public ILogParser {
public:
    QMap<QString, QList<QDate>> parseFileLog(const QString& filePath) override;
    QMap<QString, QList<QDate>> parseLogText(const QString& logText) override;

private:
    QMap<QString, QList<QDate>> extractInviteDates(const QString& logText);
};

#endif
