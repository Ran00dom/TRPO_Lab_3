#include "adapter.h"

SampleChartModelAdapter::SampleChartModelAdapter(SampleChart* _sample, QObject* parent):FileExplorerModel(parent), sample(_sample)
{
    sample = _sample;
    chart = sample->createChart(sizeMap);
}

SampleChartModelAdapter::~SampleChartModelAdapter()
{
    delete sample;
    delete chart;
}

void SampleChartModelAdapter::updateModel(QMap<QString, qint64> map)
{
    sizeMap = map;
    qDebug() << sizeMap;

    viewChart->setChart(sample->createChart(sizeMap));
    delete chart;
    chart = viewChart->chart();
}


void SampleChartModelAdapter::createView()
{
    viewChart = new QChartView(sample->createChart(sizeMap));
    view = viewChart;
}


FileExplorerListModel::FileExplorerListModel(QObject* parent):FileExplorerModel(parent)
{

}

void FileExplorerListModel::createView() {
    QListView* list = new QListView();
    list->setModel(this);
    view = list;
}
