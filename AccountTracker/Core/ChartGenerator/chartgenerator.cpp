#include "chartgenerator.h"

#include <QtCharts>
#include <QtCharts/QDateTimeAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QCategoryAxis>

ChartGenerator::ChartGenerator() {}

QChart* ChartGenerator::createInvitesChart(const QMap<QDate, int>& dailyInvitesCount)
{
    // Handle the case where the map is empty
    if (dailyInvitesCount.isEmpty())
    {
        QChart* emptyChart = new QChart();
        emptyChart->setTitle("No Data Available");
        return emptyChart;
    }

    QLineSeries* lineSeries = new QLineSeries();

    // Ensure all dates between the first and last date are covered, including one day earlier
    QDate firstDate = dailyInvitesCount.firstKey().addDays(-1);
    QDate lastDate = dailyInvitesCount.lastKey();

    // Fill in all dates between first and last date with zero invites if not already present
    for (QDate date = firstDate; date <= lastDate; date = date.addDays(1))
    {
        int inviteCount = dailyInvitesCount.value(date, 0);
        lineSeries->append(date.toJulianDay(), inviteCount);
    }

    QChart* chart = new QChart();
    chart->addSeries(lineSeries);

    // Configure X-axis as a category axis with dates
    QCategoryAxis* axisX = new QCategoryAxis();
    for (QDate date = firstDate; date <= lastDate; date = date.addDays(1))
        axisX->append(date.toString("dd.MM"), date.toJulianDay());

    axisX->setTitleText("Date");
    axisX->setLabelsAngle(45); // Rotate labels by 45 degrees

    // Configure Y-axis as an integer axis with all integer values between 0 and max count of invites
    QValueAxis* axisY = new QValueAxis();
    axisY->setTitleText("Invites");
    int maxY = *std::max_element(dailyInvitesCount.begin(), dailyInvitesCount.end());
    axisY->setRange(0, maxY); // Full range from 0 to max value
    axisY->setTickInterval(1); // Ensure that the tick interval covers all integer values
    axisY->setLabelFormat("%d"); // Display Y-axis labels as integers
    axisY->applyNiceNumbers();

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    lineSeries->attachAxis(axisX);
    lineSeries->attachAxis(axisY);

    chart->setTitle("Invites Over Time");

    chart->legend()->hide();
    return chart;
}



// QChart* ChartGenerator::createInvitesChart(const QMap<QDate, int>& dailyInvitesCount)
// {
//     QBarSeries* barSeries = new QBarSeries();
//     QBarSet* barSet = new QBarSet("Invites");
//     QStringList categories; // For storing x-axis labels (dates as strings)
//     QList<int> yValues;     // For Y-axis range calculation

//     // Populate bar set and x-axis categories with non-zero data
//     for (auto it = dailyInvitesCount.begin(); it != dailyInvitesCount.end(); ++it) {
//         if (it.value() > 0) {
//             *barSet << it.value();
//             categories << it.key().toString("dd-MM-yyyy");
//             yValues.append(it.value());
//         }
//     }

//     // Handle cases with no data
//     if (categories.isEmpty())
//         return nullptr;

//     barSeries->append(barSet);

//     QChart* chart = new QChart();
//     chart->addSeries(barSeries);

//     // Configure X-axis as a category axis with non-zero dates
//     QCategoryAxis* axisX = new QCategoryAxis();
//     for (int i = 0; i < categories.size(); ++i)
//         axisX->append(categories[i], i); // Map each date string to its index
//     axisX->setTitleText("Date");
//     axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue); // Align labels under bars
//     axisX->setLabelsAngle(45); // Rotate labels by 45 degrees for better readability

//     // Configure Y-axis as an integer axis with step = 1 and adjusted range
//     QValueAxis* axisY = new QValueAxis();
//     axisY->setTitleText("Invites");
//     int maxY = *std::max_element(yValues.begin(), yValues.end());
//     axisY->setRange(0, maxY); // Ensure the range covers the highest value
//     axisY->setTickInterval(1);
//     axisY->setLabelFormat("%i"); // Ensure integer display

//     // Ensure all integer values are displayed on the Y-axis
//     axisY->applyNiceNumbers();

//     chart->addAxis(axisX, Qt::AlignBottom);
//     chart->addAxis(axisY, Qt::AlignLeft);
//     barSeries->attachAxis(axisX);
//     barSeries->attachAxis(axisY);

//     chart->setTitle("Invites Over Time");

//     chart->legend()->hide();
//     return chart;
// }
