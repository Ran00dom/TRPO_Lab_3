#include "fileexplorermodel.h"
#include "qdebug.h"
#include "qtableview.h"
#include <cmath>

FileExplorerModel::FileExplorerModel(QObject* parent):QAbstractTableModel(parent),sizeMap(QMap<QString,qint64>()) {

}

FileExplorerModel::~FileExplorerModel(){
}

int FileExplorerModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return sizeMap.count();
}

int FileExplorerModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return LAST_HEAD;
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
        case PERCENT:
            return QString("Процент");
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
    case PERCENT: {
        if (size != 0) {
            if ((sizeMap.values().at(index.row()) * 100000 / size) >= 10)
                return QString::number((round(((double)sizeMap.values().at(index.row()) * 10000 / size) - 0.5)/100))  + "%";
            else
                if (sizeMap.values().at(index.row()) != 0)
                    return " < 0.01%";
        }
        return " * "; // вывод если нет размера
    }
    }
    return QVariant();
}

void FileExplorerModel::updateModel(QMap<QString, qint64> map) {
    sizeMap = map;
    qDebug() << sizeMap;

    size = 0;
    foreach (const qint64 value, sizeMap.values())
        size += value;


    emit layoutChanged(); // обновить представление
}

void FileExplorerModel::createView() {
    QTableView* table = new QTableView();
    table->setModel(this);
    view = table;
}

QAbstractScrollArea* FileExplorerModel::getView() {
    return view;
}
