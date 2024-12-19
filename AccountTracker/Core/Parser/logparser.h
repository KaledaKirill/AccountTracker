#ifndef LOGPARSER_H
#define LOGPARSER_H

#include "ILogParser.h"
#include "../../Utils/logger.h"

#include <QString>
#include <QMap>
#include <QList>
#include <QDate>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

class LogParser : public ILogParser
{
public:
    QMap<QString, QList<QDateTime>> parseFileLog(const QString& filePath) override;
    QMap<QString, QList<QDateTime>> parseLogText(const QString& logText) override;

private:
    QMap<QString, QList<QDateTime>> extractInviteDates(const QString& logText);

    Logger _log;
};

#endif
