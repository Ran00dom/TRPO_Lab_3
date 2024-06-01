#ifndef FILEEXPLORERMODEL_H
#define FILEEXPLORERMODEL_H

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

public slots:
    virtual void updateModel(QMap<QString, qint64>);

private:
    enum HeaderName
    {
        NAME = 0,
        SIZE,
        PERCENT,
        LAST_HEAD
    };

    qint64 size;
    QMap<QString, qint64> sizeMap;
};

#endif // FILEEXPLORERMODEL_H
