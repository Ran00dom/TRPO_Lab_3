#ifndef ADAPTER_H
#define ADAPTER_H
#include "fileexplorermodel.h"
#include "samplechart.h"

class SampleChartAdapter : public FileExplorerModel
{
public:
    SampleChartAdapter(QObject* parent = nullptr);
    ~SampleChartAdapter();

private:
    SampleChart* sample;
};

#endif // ADAPTER_H
