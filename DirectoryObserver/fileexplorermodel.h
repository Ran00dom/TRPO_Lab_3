#ifndef FILEEXPLORERMODEL_H
#define FILEEXPLORERMODEL_H

#include "calculatordirsize.h"
#include <QFileSystemModel>

class FileExplorerModel : public QFileSystemModel
{
public:
    FileExplorerModel(QObject* parent = nullptr, QMap<QString, qint64> map = {} ):QFileSystemModel(parent),sizeMap(map),calculator(new CalculateFolderSize()) {
        this->connect(this,&FileExplorerModel::rootPathChanged, this, &FileExplorerModel::updateModel);
    }
    int rowCounter(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private slots:
    void updateModel();

private:
    enum HeaderName
    {
        NAME = 0,
        SIZE
    };
    QMap<QString, qint64> sizeMap;
    CalculatorDirSize calculator;
};

#endif // FILEEXPLORERMODEL_H
