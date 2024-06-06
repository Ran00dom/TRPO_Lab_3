#ifndef FILEEXPLORERMODEL_H
#define FILEEXPLORERMODEL_H

#include "qabstractscrollarea.h"
#include <QFileSystemModel>

class FileExplorerModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    FileExplorerModel(QObject* parent = nullptr);
    ~FileExplorerModel();
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QAbstractScrollArea* getView();
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual void createView();

public slots:
    virtual void updateModel(QMap<QString, qint64>);

protected:
    enum HeaderName
    {
        NAME = 0,
        SIZE,
        PERCENT,
        LAST_HEAD
    };

    qint64 size;
    QMap<QString, qint64> sizeMap;
    QAbstractScrollArea * view;
};

#endif // FILEEXPLORERMODEL_H
