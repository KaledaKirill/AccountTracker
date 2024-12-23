#include "chartgenerator.h"

ChartGenerator::ChartGenerator()
{
}

QChart* ChartGenerator::createInvitesChart(const QMap<QDate, int>& dailyInvitesCount)
{
    QLineSeries* series = new QLineSeries();

    for (auto it = dailyInvitesCount.begin(); it != dailyInvitesCount.end(); ++it)
    {
        series->append(it.key().toJulianDay(), it.value());
    }

    QChart* chart = new QChart();
    setupChart(chart, "Daily Invites Count", "Date", "Invites");

    chart->addSeries(series);

    QValueAxis* axisX = new QValueAxis();
    axisX->setLabelFormat("%d-%m-%Y");
    axisX->setTitleText("Date");

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("Invites");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    return chart;
}

QChart* ChartGenerator::createInviteTimesChart(const QList<QDateTime>& inviteTimes)
{
    QLineSeries* series = new QLineSeries();

    for (int i = 0; i < inviteTimes.size(); ++i)
    {
        series->append(i, inviteTimes[i].toMSecsSinceEpoch());
    }

    QChart* chart = new QChart();
    setupChart(chart, "Invite Times", "Index", "Timestamp");

    chart->addSeries(series);

    QValueAxis* axisX = new QValueAxis();
    axisX->setTitleText("Index");

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("Timestamp (ms)");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    return chart;
}

void ChartGenerator::setupChart(QChart* chart, const QString& title, const QString& xAxisLabel, const QString& yAxisLabel)
{
    chart->setTitle(title);

    QValueAxis* axisX = new QValueAxis();
    axisX->setLabelFormat("%d");
    axisX->setTitleText(xAxisLabel);

    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText(yAxisLabel);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
}
