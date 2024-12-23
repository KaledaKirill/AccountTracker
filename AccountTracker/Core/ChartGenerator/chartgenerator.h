#ifndef CHARTGENERATOR_H
#define CHARTGENERATOR_H

#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QDate>
#include <QMap>
#include <QList>

class ChartGenerator
{
public:
    ChartGenerator();

    QChart* createInvitesChart(const QMap<QDate, int>& dailyInvitesCount);
    QChart* createInviteTimesChart(const QList<QDateTime>& inviteTimes);

};

#endif
