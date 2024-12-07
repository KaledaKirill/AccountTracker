#include "database.h"

DataBase* DataBase::getInstance()
{
    static DataBase instance;
    return &instance;
}

void DataBase::connect()
{
    _dataBase = QSqlDatabase::addDatabase("QSQLITE");
    QString path = "../Accounts.db";
    _dataBase.setDatabaseName(path);
    if (_dataBase.open()) {
        _log.info(__FILE__, "Connection with database was successful");
        createTables();
    } else {
        _log.error(__FILE__, "Connection with database wasn't successful. Path to DB: " + path);
        exit(EXIT_FAILURE);
    }
}

void DataBase::createTables()
{
    QSqlQuery query;

    QString createAccountsTable =
        "CREATE TABLE IF NOT EXISTS ACCOUNTS ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "account_name TEXT NOT NULL, "
        "seller_name TEXT NOT NULL, "
        "purchase_date TEXT NOT NULL, "
        "invites_count INTEGER"
        ");";

    if (!query.exec(createAccountsTable)) {
        _log.error(__FILE__, "Error creating ACCOUNTS table: " + query.lastError().text());
        exit(EXIT_FAILURE);
    } else {
        _log.info(__FILE__, "ACCOUNTS table created successfully.");
    }

    QString createDailyInvitesTable =
        "CREATE TABLE IF NOT EXISTS DAILY_INVITES ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "account_id INTEGER NOT NULL, "
        "date TEXT NOT NULL, "
        "invites_count INTEGER NOT NULL, "
        "FOREIGN KEY(account_id) REFERENCES ACCOUNTS(id) ON DELETE CASCADE"
        ");";

    if (!query.exec(createDailyInvitesTable)) {
        _log.error(__FILE__, "Error creating DAILY_INVITES table: " + query.lastError().text());
        exit(EXIT_FAILURE);
    } else {
        _log.info(__FILE__, "DAILY_INVITES table created successfully.");
    }
}

