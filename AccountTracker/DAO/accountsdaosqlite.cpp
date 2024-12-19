#include "AccountsDAOSQLite.h"
#include "../Core/Entities/account.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QList>

AccountsDAOSQLite::AccountsDAOSQLite() {}

void AccountsDAOSQLite::addInvites(int accountId, const QList<QDateTime>& inviteTimes)
{
    QSqlQuery inviteQuery;
    for (const auto& inviteTime : inviteTimes) {
        inviteQuery.prepare("INSERT INTO Invites (account_id, invite_time) VALUES (:account_id, :invite_time)");
        inviteQuery.bindValue(":account_id", accountId);
        inviteQuery.bindValue(":invite_time", inviteTime);

        if (!inviteQuery.exec()) {
            _log.error(__FILE__, "Error adding invite time: " + inviteQuery.lastError().text());
        }
    }

    _log.info(__FILE__, "Added " + QString::number(inviteTimes.size()) + " invites for account ID: " + QString::number(accountId));
}

void AccountsDAOSQLite::clearInvites(int accountId)
{
    QSqlQuery deleteInvitesQuery;
    deleteInvitesQuery.prepare("DELETE FROM Invites WHERE account_id = :account_id");
    deleteInvitesQuery.bindValue(":account_id", accountId);

    if (!deleteInvitesQuery.exec()) {
        _log.error(__FILE__, "Error deleting invites for account ID: " + deleteInvitesQuery.lastError().text());
    }

    _log.info(__FILE__, "Cleared invites for account ID: " + QString::number(accountId));
}

QList<QDateTime> AccountsDAOSQLite::getInviteTimes(int accountId)
{
    QList<QDateTime> inviteTimes;
    QSqlQuery invitesQuery;
    invitesQuery.prepare("SELECT invite_time FROM Invites WHERE account_id = :account_id");
    invitesQuery.bindValue(":account_id", accountId);

    if (invitesQuery.exec()) {
        while (invitesQuery.next()) {
            QDateTime inviteTime = invitesQuery.value(0).toDateTime();
            inviteTimes.append(inviteTime);
        }
    } else {
        _log.error(__FILE__, "Error fetching invites for account ID: " + invitesQuery.lastError().text());
    }

    return inviteTimes;
}

Account AccountsDAOSQLite::getAccountByName(const QString& accountName)
{
    QSqlQuery query;
    query.prepare("SELECT id, account_name, seller_name, purchase_date, invites_count, description FROM Accounts WHERE account_name = :account_name");
    query.bindValue(":account_name", accountName);

    if (!query.exec()) {
        _log.error(__FILE__, "Error fetching account by name: " + query.lastError().text());
        return Account("", "", QDate(), 0, "", {});
    }

    if (query.next()) {
        int accountId = query.value(0).toInt();
        QString sellerName = query.value(2).toString();
        QDate purchaseDate = query.value(3).toDate();
        int invitesCount = query.value(4).toInt();
        QString description = query.value(5).toString();

        QList<QDateTime> inviteTimes = getInviteTimes(accountId);

        _log.info(__FILE__, "Fetched account by name: " + accountName);
        return Account(accountName, sellerName, purchaseDate, invitesCount, description, inviteTimes);
    }

    _log.warning(__FILE__, "Account not found with name: " + accountName);
    return Account("", "", QDate(), 0, "", {});
}

QList<QString> AccountsDAOSQLite::getAllAccountNames()
{
    QList<QString> accountNames;
    QSqlQuery query("SELECT account_name FROM Accounts");

    if (!query.exec()) {
        _log.error(__FILE__, "Error fetching account names: " + query.lastError().text());
        return accountNames;
    }

    while (query.next()) {
        accountNames.append(query.value("account_name").toString());
    }

    _log.info(__FILE__, "Fetched all account names");
    return accountNames;
}

void AccountsDAOSQLite::addAccount(const Account& account)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Accounts (account_name, seller_name, purchase_date, invites_count, description) "
                  "VALUES (:account_name, :seller_name, :purchase_date, :invites_count, :description)");

    query.bindValue(":account_name", account.getAccountName());
    query.bindValue(":seller_name", account.getSellerName());
    query.bindValue(":purchase_date", account.getPurchaseDate().toString("yyyy-MM-dd"));
    query.bindValue(":invites_count", account.getInvitesCount());
    query.bindValue(":description", account.getDescription());

    if (!query.exec()) {
        _log.error(__FILE__, "Error adding account: " + query.lastError().text());
        return;
    }

    int accountId = query.lastInsertId().toInt();
    addInvites(accountId, account.getInvitesTime());
}

void AccountsDAOSQLite::updateAccount(const Account& oldAccount, const Account& newAccount)
{
    QSqlQuery query;
    query.prepare("UPDATE Accounts SET account_name = :new_account_name, seller_name = :seller_name, "
                  "purchase_date = :purchase_date, invites_count = :invites_count, description = :description "
                  "WHERE account_name = :old_account_name");

    query.bindValue(":new_account_name", newAccount.getAccountName());
    query.bindValue(":seller_name", newAccount.getSellerName());
    query.bindValue(":purchase_date", newAccount.getPurchaseDate().toString("yyyy-MM-dd"));
    query.bindValue(":invites_count", newAccount.getInvitesCount());
    query.bindValue(":description", newAccount.getDescription());
    query.bindValue(":old_account_name", oldAccount.getAccountName());

    if (!query.exec()) {
        _log.error(__FILE__, "Error updating account: " + query.lastError().text());
        return;
    }

    QSqlQuery getIdQuery;
    getIdQuery.prepare("SELECT id FROM Accounts WHERE account_name = :old_account_name");
    getIdQuery.bindValue(":old_account_name", oldAccount.getAccountName());

    if (!getIdQuery.exec() || !getIdQuery.next()) {
        _log.error(__FILE__, "Error fetching account ID: " + getIdQuery.lastError().text());
        return;
    }

    int accountId = getIdQuery.value(0).toInt();
    clearInvites(accountId);
    addInvites(accountId, newAccount.getInvitesTime());
}

void AccountsDAOSQLite::deleteAccountByName(const QString& accountName)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Accounts WHERE account_name = :account_name");
    query.bindValue(":account_name", accountName);

    if (!query.exec()) {
        _log.error(__FILE__, "Error deleting account: " + query.lastError().text());
        return;
    }

    _log.info(__FILE__, "Account deleted: " + accountName);
}
