#ifndef FILEEXPLORERMODEL_H
#define FILEEXPLORERMODEL_H

#include "calculatordirsize.h"
#include <QFileSystemModel>

class FileExplorerModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    FileExplorerModel(QObject* parent = nullptr, QMap<QString, qint64> map = QMap<QString, qint64>() ):QAbstractTableModel(parent),sizeMap(map),calculator(new CalculateTypeSize()) {
        //this->connect(this,&FileExplorerModel::rootPathChanged, this, &FileExplorerModel::updateModel);
    }
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void setNewPath(const QString& newPath) {path = newPath;}
public slots:
    void updateModel();


private:
    enum HeaderName
    {
        NAME = 0,
        SIZE
    };
    QMap<QString, qint64> sizeMap;
    CalculatorDirSize calculator;
    QString path;
};

#endif // FILEEXPLORERMODEL_H
