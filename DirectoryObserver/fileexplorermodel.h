#ifndef FILEEXPLORERMODEL_H
#define FILEEXPLORERMODEL_H

#include <QFileSystemModel>

class FileExplorerModel : public QFileSystemModel
{
public:
    FileExplorerModel(QObject* parent = nullptr, QMap<QString, qint64> map = {} ):QFileSystemModel(parent),sizeMap(map) {}
    int rowCounter(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QMap<QString, qint64> sizeMap;
};

#endif // FILEEXPLORERMODEL_H
