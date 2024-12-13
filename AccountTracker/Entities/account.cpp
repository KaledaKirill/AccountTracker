#include "account.h"

Account::Account()
    : _accountName("")
    , _sellerName("")
    , _purchaseDate(QDate())
    , _invitesCount(0) {}

Account::Account(const QString& accountName, const QString& sellerName, const QDate& purchaseDate, int invitesCount)
    : _accountName(accountName)
    , _sellerName(sellerName)
    , _purchaseDate(purchaseDate)
    , _invitesCount(invitesCount) {}

QString Account::getAccountName() const
{
    return _accountName;
}

QString Account::getSellerName() const
{
    return _sellerName;
}

QDate Account::getPurchaseDate() const
{
    return _purchaseDate;
}

int Account::getInvitesCount() const
{
    return _invitesCount;
}

int Account::getDailyInvites(const QDate& date) const
{
    if (_dailyInvites.contains(date))
    {
        return _dailyInvites.value(date);
    }
    return 0;
}

void Account::setInvitesCount(int count)
{
    _invitesCount = count;
}

void Account::addInvites(int count)
{
    _invitesCount += count;
}

void Account::addDailyInvites(const QDate& date, int count)
{
    if (_dailyInvites.contains(date)) {
        _dailyInvites[date] += count;
    } else {
        _dailyInvites.insert(date, count);
    }
}
