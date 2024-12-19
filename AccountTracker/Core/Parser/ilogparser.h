#ifndef ILOGPARSER_H
#define ILOGPARSER_H

#include <QString>
#include <QMap>
#include <QList>
#include <QDate>

class ILogParser
{
public:
    virtual QMap<QString, QList<QDateTime>> parseFileLog(const QString& filePath) = 0;
    virtual QMap<QString, QList<QDateTime>> parseLogText(const QString& logText) = 0;
    virtual ~ILogParser() = default;
};

#endif
