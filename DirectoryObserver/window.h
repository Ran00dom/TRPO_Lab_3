#ifndef WINDOW_H
#define WINDOW_H

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
    QTreeView *tree;
    QTableView *table;
    FileExplorerModel *modelTable;
    QFileSystemModel *modelTree;
    QPushButton* calculateButton;
    QFrame* topMenuFrame;
    QComboBox* strategyCB;

    QComboBox* viewDataCB;


public slots:
    void userSelectDir(const QModelIndex &index);
};

#endif // WINDOW_H
