#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QDate>
#include <QMap>

class Account
{
public:
    Account();
    Account(const QString& accountName, const QString& sellerName, const QDate& purchaseDate, int invitesCount);

    QString getAccountName() const;
    QString getSellerName() const;
    QDate getPurchaseDate() const;
    int getInvitesCount() const;
    int getDailyInvites(const QDate& date) const;

    void setInvitesCount(int count);
    void addInvites(int count);
    void addDailyInvites(const QDate& date, int count);

private:
    QString _accountName;
    QString _sellerName;
    QDate _purchaseDate;
    int _invitesCount;
    QMap<QDate, int> _dailyInvites;

};

#endif
