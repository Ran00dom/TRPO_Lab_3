#ifndef FILEEXPLORERMODEL_H
#define FILEEXPLORERMODEL_H

#include "calculatordirsize.h"
#include <QFileSystemModel>

class FileExplorerModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    FileExplorerModel(QObject* parent = nullptr);
    ~FileExplorerModel();
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void setNewPath(const QString& newPath) {path = newPath;}
public slots:
    void updateModel();
    void selectStrategy(int strategy);

private:
    enum HeaderName
    {
        NAME = 0,
        SIZE
    };
    enum StrategyType
    {
        DIR_SIZE = 0,
        TYPE_SIZE
    };
    QMap<QString, qint64> sizeMap;
    CalculatorDirSize* calculator;
    CalculateDirectory* strategyCalc[TYPE_SIZE + 1];
    QString path;
};

#endif // FILEEXPLORERMODEL_H
