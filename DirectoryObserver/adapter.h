#ifndef ADAPTER_H
#define ADAPTER_H
#include "fileexplorermodel.h"
#include "samplechart.h"
#include <QChart>

class SampleChartModelAdapter : public FileExplorerModel
{
public:
    SampleChartModelAdapter(SampleChart* _sample, QObject* parent = nullptr);
    ~SampleChartModelAdapter();
    void createView();
    void updateModel(QMap<QString, qint64>);
private:
    SampleChart* sample;
    QChart* chart;
    QChartView* viewChart;
};

#endif // ADAPTER_H
