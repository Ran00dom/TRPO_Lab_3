#include "window.h"
#include "samplechart.h"

Window::Window(QWidget *parent): QWidget{parent}
{
    tree = new QTreeView(this);
    table = new QTableView(this);
    modelTable = new FileExplorerModel(this);
    modelTree = new QFileSystemModel(this);
    topMenuFrame = new QFrame(this);
    calculateButton = new QPushButton("Calculate",this);
    strategyCB = new QComboBox(this);
    viewDataCB = new QComboBox(this);

    modelTree->setRootPath(QDir::homePath());
    tree->setModel(modelTree);
    table->setModel(modelTable);

    viewDataCB->addItem("Таблица", 0);
    viewDataCB->addItem("Круговая диаграмма", 1);
    viewDataCB->addItem("Гистограмма", 2);

    strategyCB->addItem("Directory Size", 0);
    strategyCB->addItem("File Type Size", 1);
    topMenuFrame->setFrameShadow(QFrame::Raised);
    topMenuFrame->setFrameShape(QFrame::Panel);

    SampleChart* sampleChart = new BarChart();
    QMap<QString, qint64> map;
    map.insert("txt", 10);
    map.insert("doc", 20);

    QChartView *view = new QChartView(sampleChart->createChart(map));

    QHBoxLayout *hLayout1 = new QHBoxLayout();
    hLayout1->addWidget(tree);
    hLayout1->addWidget(table);
    hLayout1->addWidget(view);

    QHBoxLayout *hLayout2 = new QHBoxLayout(topMenuFrame);
    hLayout2->addWidget(calculateButton);
    hLayout2->addWidget(strategyCB);
    hLayout2->addWidget(viewDataCB);

    QVBoxLayout *vLayout1 = new QVBoxLayout(this);
    vLayout1->addWidget(topMenuFrame);
    vLayout1->addLayout(hLayout1);

    tree->show();
    table->show();

    connect(tree, &QTableView::pressed, this, &Window::userSelectDir);
    connect(calculateButton, &QPushButton::pressed, modelTable , &FileExplorerModel::updateModel);
    connect(strategyCB, qOverload<int>(&QComboBox::currentIndexChanged), modelTable, &FileExplorerModel::selectStrategy);
}

void Window::userSelectDir(const QModelIndex &index){
    modelTable->setNewPath(modelTree->filePath(index));
}
