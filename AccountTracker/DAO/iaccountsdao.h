#ifndef IACCOUNTSDAO_H
#define IACCOUNTSDAO_H

#include "../Core/Entities/account.h"
#include <QList>

class IAccountsDAO
{
public:
    virtual ~IAccountsDAO() = default;

    virtual Account getAccountByName(const QString& accountName) = 0;
    virtual QList<QString> getAllAccountNames() = 0;
    virtual void addAccount(const Account& account) = 0;
    virtual void updateAccount(const Account& oldAccount, const Account& newAccount) = 0;
    virtual void deleteAccountByName(const QString& accountName) = 0;
    virtual QList<QDateTime> getInviteTimes(int accountId) = 0;

};

#endif
