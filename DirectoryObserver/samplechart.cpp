#include "samplechart.h"

QtCharts::QChart* SampleChart::createChart(QMap<QString, qint64>& data)
{
    QChart* chart = new QChart();
    createSeries(chart, data);
    drawLegend(chart->legend(), data);
    qDebug() << chart->series().at(0);
    return chart;
}

////////////////////////////////////////////////////////////////////////////////////////

void PieChart::createSeries(QtCharts::QChart* chart, QMap<QString, qint64>& data) {
    QPieSeries* series = new QPieSeries(chart);
    foreach (const QString& key, data.keys()) {
        QPieSlice* slice = new QPieSlice(series);
        slice->setLabel(key);
        slice->setValue(data.find(key).value());
        series->append(slice);
    }
    chart->addSeries(series);
}

void BarChart::createSeries(QtCharts::QChart* chart, QMap<QString, qint64>& data) {

    QBarSeries* series = new QBarSeries(chart);
    int i = 0;
    foreach (const QString& key, data.keys()) {
        QBarSet* bar = new QBarSet(key,series);
        bar->insert(i, data.find(key).value());
        series->append(bar);
        i++;
    }
    chart->addSeries(series);
}
