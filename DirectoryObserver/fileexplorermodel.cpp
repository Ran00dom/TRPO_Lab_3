#include "fileexplorermodel.h"
#include "qdebug.h"

FileExplorerModel::FileExplorerModel(QObject* parent):QAbstractTableModel(parent),sizeMap(QMap<QString,qint64>()) {
    strategyCalc[0] = new CalculateFolderSize();
    strategyCalc[1] = new CalculateTypeSize();
    calculator = new CalculatorDirSize(strategyCalc[0]);
}

FileExplorerModel::~FileExplorerModel(){
    delete calculator;
    delete strategyCalc[0];
    delete strategyCalc[1];
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
            return QString::number(sizeMap.values().at(index.row()));
        }
    }
    return QVariant();
}

void FileExplorerModel::updateModel() {
    sizeMap = calculator->calculate(path);
    qDebug() << sizeMap;

    size = 0;
    foreach (const qint64 value, sizeMap.values())
        size += value;

    if (strategy == TYPE_SIZE && sizeMap.count() > 0) {
        qint64 otherSize = 0;
        foreach (const QString key, sizeMap.keys()) {
            if (sizeMap.find(key).value() == 0 || (sizeMap.find(key).value() * 100000 / size) < 10) {
                otherSize += sizeMap.find(key).value();
                sizeMap.remove(key);
            }
        }
        if (otherSize > 0)
            sizeMap.insert("other", otherSize);
    }

    emit layoutChanged();
}
void FileExplorerModel::selectStrategy(int strategy) {
    qDebug() << "Strategy changed " << strategy;
    if (strategy < LAST_STRATEGY && strategy > -1) {
        calculator->setCalculate(strategyCalc[strategy]);
        this->strategy = (StrategyType)strategy;
    }
}
