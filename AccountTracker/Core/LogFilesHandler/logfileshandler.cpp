#include "../Parser/logparser.h"
#include "../../DAO/accountsdaosqlite.h"
#include "../Entities/account.h"
#include "logfileshandler.h"

#include <QDir>

LogFilesHandler::LogFilesHandler()
    : _parser(new LogParser)
    , _accountsDAO(new AccountsDAOSQLite) {}

void LogFilesHandler::handleTextLog(const QString &text)
{
    QMap<QString, QList<QDateTime>> logData = _parser->parseLogText(text);
    proccesLogData(logData);
}

void LogFilesHandler::handleFileLog(const QString &filePath)
{
    QMap<QString, QList<QDateTime>> logData = _parser->parseFileLog(filePath);
    proccesLogData(logData);
}

void LogFilesHandler::handleFolderWithLogs(const QString &folderPath)
{
    QMap<QString, QList<QDateTime>> logData;

    QDir folder(folderPath);
    if (!folder.exists())
    {
        throw std::runtime_error("Folder does not exist");
        _log.warning(__FILE__, "Folder does not exist: " + folderPath);
        return;
    }

    QStringList txtFiles = folder.entryList({"*.txt"}, QDir::Files);
    if (txtFiles.isEmpty())
    {
        throw std::runtime_error("No .txt files in folder");
        _log.warning(__FILE__, "No .txt files in folder: " + folderPath);
        return;
    }

    for (const QString &fileName : txtFiles)
    {
        QString filePath = folder.absoluteFilePath(fileName);
        logData = _parser->parseFileLog(filePath);
        proccesLogData(logData);
    }
}

void LogFilesHandler::proccesLogData(const QMap<QString, QList<QDateTime> > logData)
{
    if(logData.isEmpty())
        return;

    for (auto it = logData.begin(); it != logData.end(); ++it)
        proccesAccountData(it.key(), it.value());
}

void LogFilesHandler::proccesAccountData(const QString &accountName, const QList<QDateTime> invitesTime)
{
    Account account = _accountsDAO->getAccountByName(accountName);
    if (account.isEmpty())
        return;
    Account newAccount = account;

    for (const auto& inviteTime : invitesTime)
        newAccount.addInviteTime(inviteTime);

    _accountsDAO->updateAccount(account, newAccount);
}

