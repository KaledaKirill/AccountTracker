#include "AccountsDAOSQLite.h"
#include "../Entities/account.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QList>

AccountsDAOSQLite::AccountsDAOSQLite() {}

Account AccountsDAOSQLite::getAccountByName(const QString& accountName)
{
    QSqlQuery query;
    query.prepare("SELECT id, account_name, seller_name, purchase_date, invites_count FROM Accounts WHERE account_name = :account_name");
    query.bindValue(":account_name", accountName);

    if (!query.exec()) {
        _log.error(__FILE__, "Error fetching account by name: " + query.lastError().text());
        return Account("", "", QDate(), 0);
    }

    if (query.next()) {
        QString sellerName = query.value(2).toString();
        QDate purchaseDate = query.value(3).toDate();
        int invitesCount = query.value(4).toInt();

        _log.info(__FILE__, "Fetched account by name: " + accountName);
        return Account(accountName, sellerName, purchaseDate, invitesCount);
    }

    _log.warning(__FILE__, "Account not found with name: " + accountName);
    return Account("", "", QDate(), 0);
}

Account AccountsDAOSQLite::getAccountById(int id)
{
    QSqlQuery query;
    query.prepare("SELECT id, account_name, seller_name, purchase_date, invites_count FROM Accounts WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        _log.error(__FILE__, "Error fetching account by id: " + query.lastError().text());
        return Account("", "", QDate(), 0);
    }

    if (query.next()) {
        QString accountName = query.value(1).toString();
        QString sellerName = query.value(2).toString();
        QDate purchaseDate = query.value(3).toDate();
        int invitesCount = query.value(4).toInt();

        _log.info(__FILE__, "Fetched account by id: " + QString::number(id));
        return Account(accountName, sellerName, purchaseDate, invitesCount);
    }

    _log.warning(__FILE__, "Account not found with id: " + QString::number(id));
    return Account("", "", QDate(), 0);
}

QList<QString> AccountsDAOSQLite::getAllAccountNames()
{
    QList<QString> accountNames;
    QSqlQuery query;
    query.prepare("SELECT account_name FROM Accounts");

    if (!query.exec()) {
        _log.error(__FILE__, "Error fetching account names: " + query.lastError().text());
        return accountNames;
    }

    while (query.next()) {
        accountNames.append(query.value(0).toString());
    }

    _log.info(__FILE__, "Fetched all account names");
    return accountNames;
}

void AccountsDAOSQLite::addAccount(const Account& account)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Accounts (account_name, seller_name, purchase_date, invites_count) "
                  "VALUES (:account_name, :seller_name, :purchase_date, :invites_count)");

    query.bindValue(":account_name", account.getAccountName());
    query.bindValue(":seller_name", account.getSellerName());
    query.bindValue(":purchase_date", account.getPurchaseDate().toString("yyyy-MM-dd"));
    query.bindValue(":invites_count", account.getInvitesCount());

    if (!query.exec()) {
        _log.error(__FILE__, "Error adding account: " + query.lastError().text());
        return;
    }

    _log.info(__FILE__, "Account added: " + account.getAccountName());
}

void AccountsDAOSQLite::updateAccount(const Account& account)
{
    QSqlQuery query;
    query.prepare("UPDATE Accounts SET account_name = :account_name, seller_name = :seller_name, "
                  "purchase_date = :purchase_date, invites_count = :invites_count "
                  "WHERE id = :id");

    query.bindValue(":account_name", account.getAccountName());
    query.bindValue(":seller_name", account.getSellerName());
    query.bindValue(":purchase_date", account.getPurchaseDate().toString("yyyy-MM-dd"));
    query.bindValue(":invites_count", account.getInvitesCount());

    if (!query.exec()) {
        _log.error(__FILE__, "Error updating account: " + query.lastError().text());
        return;
    }

    _log.info(__FILE__, "Account updated: " + account.getAccountName());
}

void AccountsDAOSQLite::deleteAccount(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Accounts WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        _log.error(__FILE__, "Error deleting account: " + query.lastError().text());
        return;
    }

    _log.info(__FILE__, "Account deleted: " + QString::number(id));
}
