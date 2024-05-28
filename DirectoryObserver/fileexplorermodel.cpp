#include "fileexplorermodel.h"

int FileExplorerModel::rowCounter(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return sizeMap.count();
}

int FileExplorerModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return 2;
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
    if (!index.isValid() ||
        sizeMap.count() <= index.row() || (role != Qt::DisplayRole && role != Qt::EditRole))
    {
        return QVariant();
    }

    switch (index.column()) {
    case NAME:
        return sizeMap.key(index.row());
    case SIZE:
        return sizeMap.value(sizeMap.key(index.row()));
    }
    return QVariant();
}

void FileExplorerModel::updateModel() {
    sizeMap = calculator.calculate(rootPath());
}
