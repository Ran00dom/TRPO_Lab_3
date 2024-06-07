#ifndef SAMPLECHART_H
#define SAMPLECHART_H

#include <QtCharts>

//using namespace QtCharts;

class SampleChart
{
public:
    SampleChart() {};

    QtCharts::QChart* createChart(QMap<QString, qint64>&);
protected:
    virtual void createSeries(QtCharts::QChart*, QMap<QString, qint64>&) = 0;
    virtual void drawLegend (QLegend* ,QMap<QString, qint64>&) = 0;
};


class PieChart : public SampleChart
{
protected:
    void createSeries(QtCharts::QChart*, QMap<QString, qint64>&);
    void drawLegend (QLegend* ,QMap<QString, qint64>&) {};
};

class BarChart : public SampleChart
{
protected:
    void createSeries(QtCharts::QChart*, QMap<QString, qint64>&);
    void drawLegend (QLegend* ,QMap<QString, qint64>&) {};
};

#endif // SAMPLECHART_H
