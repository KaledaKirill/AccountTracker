#ifndef IACCOUNTSDAO_H
#define IACCOUNTSDAO_H

#include "../Entities/account.h"
#include <QList>

class IAccountsDAO
{
public:
    virtual ~IAccountsDAO() = default;

    virtual Account getAccountByName(const QString& accountName) = 0;
    virtual Account getAccountById(int id) = 0;
    virtual QList<QString> getAllAccountNames() = 0;
    virtual void addAccount(const Account& account) = 0;
    virtual void updateAccount(const Account& account) = 0;
    virtual void deleteAccount(int id) = 0;

};

#endif
