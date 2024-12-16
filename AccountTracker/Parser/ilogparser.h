#ifndef ILOGPARSER_H
#define ILOGPARSER_H

#include <QString>
#include <QMap>
#include <QList>
#include <QDate>

class ILogParser
{
public:
    virtual QMap<QString, QList<QDate>> parseFileLog(const QString& filePath) = 0;
    virtual QMap<QString, QList<QDate>> parseLogText(const QString& logText) = 0;
    virtual ~ILogParser() = default;
};

#endif
