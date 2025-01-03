#include "account.h"

Account::Account()
    : _accountName("")
    , _sellerName("")
    , _purchaseDate(QDate())
    , _invitesCount(0) {}

Account::Account(const QString& accountName, const QString& sellerName, const QDate& purchaseDate, int invitesCount, const QString& description, const QList<QDateTime> invitesTime)
    : _accountName(accountName)
    , _sellerName(sellerName)
    , _purchaseDate(purchaseDate)
    , _invitesCount(invitesCount)
    , _invitesTime(invitesTime)
    , _description(description) {}

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

QList<QDateTime> Account::getInvitesTime() const
{
    return _invitesTime;
}

QString Account::getDescription() const
{
    return _description;
}

void Account::addInvites(int count)
{
    _invitesCount += count;
}

void Account::increaseInvites()
{
    _invitesCount++;
}

void Account::addInviteTime(const QDateTime &inviteTime)
{
    if (!_invitesTime.contains(inviteTime))
    {
        _invitesTime.append(inviteTime);
        increaseInvites();
    }
}

void Account::updateAccount(const QString &accountName, const QString &sellerName, const QDate &purchaseDate, const QString &description)
{
    _accountName = accountName;
    _sellerName = sellerName;
    _purchaseDate = purchaseDate;
    _description = description;
}

bool Account::isEmpty()
{
    return _accountName.isEmpty() && _sellerName.isEmpty() && !_purchaseDate.isValid() && _invitesCount == 0 && _description.isEmpty();
}

QMap<QDate, int> Account::getDailyInvitesCount() const
{
    QMap<QDate, int> dailyCount;

    for (const QDateTime& inviteTime : _invitesTime)
    {
        QDate date = inviteTime.date();
        dailyCount[date]++;
    }

    return dailyCount;
}

QMap<QDate, int> Account::getDailyInvitesCount(const QDate& startDate, const QDate& endDate) const
{
    QMap<QDate, int> dailyCount;

    for (const QDateTime& inviteTime : _invitesTime)
    {
        QDate date = inviteTime.date();

        if (date >= startDate && date <= endDate)
            dailyCount[date]++;
    }

    return dailyCount;
}

QList<QDateTime> Account::getDayliInviteTimes(const QDate& date) const
{
    QList<QDateTime> dailyTimes;

    for (const QDateTime& inviteTime : _invitesTime)
    {
        if (inviteTime.date() == date)
            dailyTimes.append(inviteTime);
    }

    return dailyTimes;
}
