#include "calculatedirectory.h"

QMap<QString, qint64> CalculateTypeSize::calculate(QString directory, QString mapCatalog, int level)
{
    Q_UNUSED(mapCatalog)
    QMap<QString, qint64> map;

    if (!level) {
        QFileInfo file(directory);
        if (file.isFile()) {
            map.insert(file.suffix(), file.size());
            return map;
        }
    }

    if (exists(directory)) {
        this->cd(directory);
        for (const QFileInfo& file : this->entryInfoList(QDir::Files))
            map.insert(file.suffix(), map.contains(file.suffix()) ? map.find(file.suffix()).value() + file.size() : file.size());

        QMap<QString, qint64> dirMap;
        for (const QString &dir : this->entryList(QDir::NoDotAndDotDot | QDir::Dirs))
        {
            dirMap = this->calculate(directory + "\\" + dir, "", 1);
            for (auto i = dirMap.cbegin(), end = dirMap.cend(); i != end; ++i)
                map.insert(i.key(), map.contains(i.key()) ? map.find(i.key()).value() + i.value() : i.value());
        }
    }

    if (!level)
        this->cd(directory);

    return map;
}

QMap<QString, qint64> CalculateFolderSize::calculate(QString directory, QString mapCatalog, int level)
{
    QMap<QString, qint64> map;

    if (!level) {
        QFileInfo file(directory);
        if (file.isFile()) {
                map.insert("Current Folder", file.size());
                return map;
        }
        mapCatalog = "Current Folder";
    }


    if (exists(directory)) {
        map.insert(mapCatalog, 0);
        this->cd(directory);
        foreach (const QFileInfo& file, this->entryInfoList(QDir::Files))
            map.insert(mapCatalog, map.contains(mapCatalog) ? map.find(mapCatalog).value() + file.size() : file.size());

        QMap<QString, qint64> dirMap;
        foreach (const QString &dir, this->entryList(QDir::NoDotAndDotDot | QDir::Dirs))
        {
            if (!level) {
                map.insert(dir, 0);
                dirMap = this->calculate(directory + "\\" + dir, dir, level + 1);
            }
            else
                dirMap = this->calculate(directory + "\\" + dir, mapCatalog, 2);
            for (auto i = dirMap.cbegin(), end = dirMap.cend(); i != end; ++i)
                map.insert(i.key(), map.contains(i.key()) ? map.find(i.key()).value() + i.value() : i.value());
        }
    }

    if (!level)
        this->cd(directory);

    return map;
}




