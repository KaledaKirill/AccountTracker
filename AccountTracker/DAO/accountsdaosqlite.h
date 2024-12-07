#ifndef ACCOUNTSDAOSQLITE_H
#define ACCOUNTSDAOSQLITE_H

#include "IAccountsDAO.h"
#include "../Utils/logger.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>

class AccountsDAOSQLite : public IAccountsDAO
{
public:
    AccountsDAOSQLite(QSqlDatabase& db);
    Account getAccountByName(const QString& accountName) override;
    Account getAccountById(int id) override;
    QList<QString> getAllAccountNames() override;
    void addAccount(const Account& account) override;
    void updateAccount(const Account& account) override;
    void deleteAccount(int id) override;

private:
    QSqlDatabase& _db;
    Logger _log;

};

#endif
