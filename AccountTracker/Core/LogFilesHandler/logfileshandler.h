#ifndef LOGFILESHANDLER_H
#define LOGFILESHANDLER_H

#include "../Parser/ilogparser.h"
#include "../../Utils/logger.h"
#include "../../DAO/iaccountsdao.h"

#include <QScopedPointer>

class LogFilesHandler
{
public:
    LogFilesHandler();

    bool handleTextLog(const QString& text);
    bool handleFileLog(const QString& filePath);

private:
    QScopedPointer<ILogParser> _parser;
    QScopedPointer<IAccountsDAO> _accountsDAO;
    Logger _log;

    bool proccesLogData(const QMap<QString, QList<QDateTime>> logData);

};

#endif
