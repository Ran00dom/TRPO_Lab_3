#include "fileexplorermodel.h"
#include "qdebug.h"
#include <cmath>

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
        if ((sizeMap.values().at(index.row()) * 100000 / size) >= 10)
                return QString::number(round(((double)sizeMap.values().at(index.row()) * 10000 / size))/100)  + "%";
        else
            if (sizeMap.values().at(index.row()) != 0)
                return " < 0.01%";
            else
               return " * "; // вывод если нет размера
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
    // выделение типов в группу other
    if (strategy == TYPE_SIZE && sizeMap.count() > 0) { // проверяем стратегию
        qint64 otherSize = 0;
        QStringList otherKey; // лист для ключей на удаление
        foreach (const QString& key, sizeMap.keys()) {
            if (sizeMap.find(key).value() == 0 || (sizeMap.find(key).value() * 100000 / size) < 10) { // условие для other
                otherSize += sizeMap.find(key).value();
                otherKey.append(key); // добавляем ключь на удаление
            }
        }
        if (otherSize > 0 && otherKey.count() > 1) { // если есть больше одного ключа в категории other
            foreach (const QString& key, otherKey) // удаление всех ключей из категории other
                sizeMap.remove(key);
            sizeMap.insert(sizeMap.constEnd(),"other", otherSize);
        }
    }

    emit layoutChanged(); // обновить представление
}
void FileExplorerModel::selectStrategy(int strategy) {
    qDebug() << "Strategy changed " << strategy;
    if (strategy < LAST_STRATEGY && strategy > -1) {
        calculator->setCalculate(strategyCalc[strategy]);
        this->strategy = (StrategyType)strategy;
    }
}
