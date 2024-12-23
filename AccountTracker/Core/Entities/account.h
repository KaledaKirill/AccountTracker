#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QDate>
#include <QList>
#include <QMap>

class Account
{
public:
    Account();
    Account(const QString& accountName, const QString& sellerName, const QDate& purchaseDate, const int invitesCount, const QString& description = "", const QList<QDateTime> invitesTime = QList<QDateTime>());

    QString getAccountName() const;
    QString getSellerName() const;
    QDate getPurchaseDate() const;
    int getInvitesCount() const;
    QList<QDateTime> getInvitesTime() const;
    QString getDescription() const;

    void addInvites(int count);
    void addInviteTime(const QDateTime& inviteTime);
    void updateAccount(const QString& accountName, const QString& sellerName, const QDate& purchaseDate, const QString& description);

    bool isEmpty();

    QMap<QDate, int> getDailyInvitesCount();
    QMap<QDate, int> getDailyInvitesCount(const QDate& startDate, const QDate& endDate);
    QList<QDateTime> getDayliInviteTimes(const QDate& date);

private:
    QString _accountName;
    QString _sellerName;
    QDate _purchaseDate;
    int _invitesCount;
    QList<QDateTime> _invitesTime;
    QString _description;

    void increaseInvites();

};

#endif
