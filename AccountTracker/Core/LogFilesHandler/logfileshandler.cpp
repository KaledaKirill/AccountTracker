#include "../Parser/logparser.h"
#include "../../DAO/accountsdaosqlite.h"
#include "../Entities/account.h"
#include "logfileshandler.h"

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

void LogFilesHandler::proccesLogData(const QMap<QString, QList<QDateTime> > logData)
{
    if(logData.isEmpty())
        throw std::runtime_error("Log is empty");

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

