#ifndef WINDOW_H
#define WINDOW_H

#include "calculatordirsize.h"
#include "fileexplorermodel.h"
#include <QWidget>
#include <QTreeView>
#include <QTableView>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>

#include <QtCharts>
#include <QStackedBarSeries>


class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = nullptr);

signals:

private:

    void updateModel();

    enum StrategyType
    {
        DIR_SIZE = 0,
        TYPE_SIZE,
        LAST_STRATEGY
    };

    FileExplorerModel *modelTable;
    QFileSystemModel *modelTree;

    QTreeView *tree;
    QTableView *table;

    QPushButton* calculateButton;
    QFrame* topMenuFrame;

    QComboBox* strategyCB;
    QComboBox* viewDataCB;

    CalculatorDirSize* context;
    CalculateDirectory* strategyCalc[LAST_STRATEGY];

    QString filePath;

public slots:
    void userSelectDir(const QModelIndex &index);
    void selectStratrgy(int strategy);
};

#endif // WINDOW_H
