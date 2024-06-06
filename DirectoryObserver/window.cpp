#include "window.h"
#include "qglobal.h"
#include "samplechart.h"

Window::Window(QWidget *parent): QWidget{parent}
{
    // создание стратегий и контекста
    strategyCalc[0] = new CalculateFolderSize();
    strategyCalc[1] = new CalculateTypeSize();
    context = new CalculatorDirSize(strategyCalc[0]);

    models.append(new FileExplorerModel(this));
    models.append(new FileExplorerListModel(this));
    models.append(new SampleChartModelAdapter(new BarChart(),this));
    models.append(new SampleChartModelAdapter(new PieChart(),this));


    foreach (FileExplorerModel* model, models) {
        model->createView();
        views.append(model->getView());
        model->getView()->setParent(this);
        strategyCalc[0]->attach(model);
        strategyCalc[1]->attach(model);
    }

    /*
    table = new QTableView(this);
    list = new QListView(this);
    pieView = new QChartView(this);
    barView = new QChartView(this);
    QAbstractScrollArea *adf = new QAbstractScrollArea();
    */

    //modelTable = new FileExplorerModel(this);


    tree = new QTreeView(this);
    modelTree = new QFileSystemModel(this);

    topMenuFrame = new QFrame(this);
    calculateButton = new QPushButton("Calculate",this);
    strategyCB = new QComboBox(this);
    viewDataCB = new QComboBox(this);

    modelTree->setRootPath(QDir::homePath());
    tree->setModel(modelTree);
    //table->setModel(modelTable);
    //list->setModel(modelTable);

    viewDataCB->addItem("Table", 0);
    viewDataCB->addItem("List", 1);
    viewDataCB->addItem("Pic", 2);
    viewDataCB->addItem("Bar", 3);

    strategyCB->addItem("Directory Size", 0);
    strategyCB->addItem("File Type Size", 1);
    topMenuFrame->setFrameShadow(QFrame::Raised);
    topMenuFrame->setFrameShape(QFrame::Panel);


    QHBoxLayout *hLayout1 = new QHBoxLayout();

    hLayout1->addWidget(tree);
    foreach (QAbstractScrollArea* view, views) {
        hLayout1->addWidget(view);
    }

    //hLayout1->addWidget(table);
    //hLayout1->addWidget(list);
    //hLayout1->addWidget(pieView);

    QHBoxLayout *hLayout2 = new QHBoxLayout(topMenuFrame);
    hLayout2->addWidget(calculateButton);
    hLayout2->addWidget(strategyCB);
    hLayout2->addWidget(viewDataCB);

    QVBoxLayout *vLayout1 = new QVBoxLayout(this);
    vLayout1->addWidget(topMenuFrame);
    vLayout1->addLayout(hLayout1);

    selectView(TABLE);
    tree->show();

    connect(tree, &QTableView::pressed, this, &Window::userSelectDir);
    connect(calculateButton, &QPushButton::pressed, this , &Window::updateModel);
    // выбор стратегии
    connect(strategyCB, qOverload<int>(&QComboBox::currentIndexChanged), this, &Window::selectStratrgy);


    /////////////////////////////////////////
    connect(viewDataCB, qOverload<int>(&QComboBox::currentIndexChanged), this, &Window::selectView);
    // подписка на обнавления стратегий
}

void Window::userSelectDir(const QModelIndex &index){
    filePath = modelTree->filePath(index);
}
void Window::selectStratrgy(int strategy){
    if (strategy < LAST_STRATEGY && strategy > -1) {
        context->setCalculate(strategyCalc[strategy]);
    }
}

void Window::selectView(int viewID){
    if (viewID < LAST_VIEW && viewID > -1) {
        foreach (QAbstractScrollArea* view, views) {
            view->hide();
        }

        views.at(viewID)->show();
    }
}

void Window::updateModel() {
    context->calculate(filePath);
}
