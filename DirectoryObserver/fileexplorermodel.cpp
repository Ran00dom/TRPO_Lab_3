#include "fileexplorermodel.h"
#include "qdebug.h"

int FileExplorerModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return sizeMap.count();
}

int FileExplorerModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return SIZE + 1;
}

QVariant FileExplorerModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    if (orientation == Qt::Vertical) {
        return section;
    }

    switch (section) {
    case NAME:
        return QString("Название");
    case SIZE:
        return QString("Размер");
    }

    return QVariant();
}

QVariant FileExplorerModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid() || sizeMap.count() < index.row() || (role != Qt::DisplayRole && role != Qt::EditRole))
    {
       return QVariant();
    }

    switch (index.column()) {
    case NAME:
        return sizeMap.keys().at(index.row());
    case SIZE:
        return QString::number(sizeMap.values().at(index.row()));
    }
    return QVariant();
}

void FileExplorerModel::updateModel() {
    sizeMap = calculator.calculate(path);
    qDebug() << sizeMap;
    emit layoutChanged();
}

