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

    void handleTextLog(const QString& text);
    void handleFileLog(const QString& filePath);
    void handleFolderWithLogs(const QString& folderPath);

private:
    QScopedPointer<ILogParser> _parser;
    QScopedPointer<IAccountsDAO> _accountsDAO;
    Logger _log;

    void proccesLogData(const QMap<QString, QList<QDateTime>> logData);
    void proccesAccountData(const QString& accountName, const QList<QDateTime> invitesTime);

};

#endif
