#include "window.h"

Window::Window(QWidget *parent): QWidget{parent}
{
    tree = new QTreeView(this);
    table = new QTableView(this);
    modelTable = new FileExplorerModel(this);
    modelTree = new QFileSystemModel(this);
    calculate = new QPushButton("Calculate",this);

    modelTree->setRootPath(QDir::homePath());
    //modelTable->setRootPath(QDir::homePath());
    tree->setModel(modelTree);

    //tree->setRootIndex(file->index(QDir::currentPath()));
    table->setModel(modelTable);

    QHBoxLayout *hLayout1 = new QHBoxLayout(this);
    hLayout1->addWidget(tree);
    hLayout1->addWidget(table);
    hLayout1->addStretch();
    tree->show();
    table->show();

    QVBoxLayout *vLayout1 = new QVBoxLayout(this);
    vLayout1->addWidget(calculate);
    vLayout1->addLayout(hLayout1);
    vLayout1->addStretch();
    connect(tree, &QTableView::pressed, this, &Window::userSelectDir);
    connect(calculate, &QPushButton::pressed, modelTable , &FileExplorerModel::updateModel);
   // connect(modelTable , &FileExplorerModel::update, table , &QTableView::updateGeometry);
}

void Window::userSelectDir(const QModelIndex &index){
    modelTable->setRootPath(modelTree->filePath(index));
}
