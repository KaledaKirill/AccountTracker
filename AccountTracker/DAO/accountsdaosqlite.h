#ifndef ACCOUNTSDAOSQLITE_H
#define ACCOUNTSDAOSQLITE_H

#include "IAccountsDAO.h"
#include "../Utils/logger.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <QDateTime>

class AccountsDAOSQLite : public IAccountsDAO
{
public:
    AccountsDAOSQLite();

    Account getAccountByName(const QString& accountName) override;
    QList<QString> getAllAccountNames() override;
    void addAccount(const Account& account) override;
    void updateAccount(const Account& oldAccount, const Account& newAccount) override;
    void deleteAccountByName(const QString& accountName) override;
    QList<QDateTime> getInviteTimes(int accountId) override;

private:
    Logger _log;

    void addInvites(int accountId, const QList<QDateTime> &inviteTimes);
    void clearInvites(int accountId);

};

#endif
