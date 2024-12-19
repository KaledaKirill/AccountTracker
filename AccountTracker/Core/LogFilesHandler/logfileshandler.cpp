#include "../Parser/logparser.h"
#include "../../DAO/accountsdaosqlite.h"
#include "logfileshandler.h"

LogFilesHandler::LogFilesHandler()
    : _parser(new LogParser)
    , _accountsDAO(new AccountsDAOSQLite) {}

bool LogFilesHandler::handleTextLog(const QString &text)
{
    QMap<QString, QList<QDateTime>> logData = _parser->parseLogText(text);
    return proccesLogData(logData);
}

bool LogFilesHandler::handleFileLog(const QString &filePath)
{
    QMap<QString, QList<QDateTime>> logData = _parser->parseFileLog(filePath);
    return proccesLogData(logData);
}

bool LogFilesHandler::proccesLogData(const QMap<QString, QList<QDateTime> > logData)
{
    if(logData.isEmpty())
        return false;

    for (auto it = logData.begin(); it != logData.end(); ++it)
    {
        qDebug() << "Account:" << it.key() << "Invites on dates:" << it.value();
    }

    return true;
}
