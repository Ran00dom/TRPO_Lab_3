#include "window.h"

Window::Window(QWidget *parent): QWidget{parent}
{
    tree = new QTreeView(this);
    table = new QTableView(this);
    modelTable = new FileExplorerModel(this);
    modelTree = new QFileSystemModel(this);
    topMenu = new QFrame(this);
    calculate = new QPushButton("Calculate",this);

    modelTree->setRootPath(QDir::homePath());
    tree->setModel(modelTree);
    table->setModel(modelTable);

    topMenu->setFrameShadow(QFrame::Raised);
    topMenu->setFrameShape(QFrame::Panel);

    QHBoxLayout *hLayout1 = new QHBoxLayout();
    hLayout1->addWidget(tree);
    hLayout1->addWidget(table);

    QHBoxLayout *hLayout2 = new QHBoxLayout(topMenu);
    hLayout2->addWidget(calculate);

    QVBoxLayout *vLayout1 = new QVBoxLayout(this);
    vLayout1->addWidget(topMenu);
    vLayout1->addLayout(hLayout1);

    tree->show();
    table->show();

    connect(tree, &QTableView::pressed, this, &Window::userSelectDir);
    connect(calculate, &QPushButton::pressed, modelTable , &FileExplorerModel::updateModel);
}

void Window::userSelectDir(const QModelIndex &index){
    modelTable->setNewPath(modelTree->filePath(index));
}
