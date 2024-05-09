#include "catalogmanager.h"

CatalogManager::CatalogManager(const QString& path) : QDir(path), baseCatalog(path)
{
    files = getFileList();
    updateSyffixMap();
}

QFileInfoList CatalogManager::getFileList(QString directory)
{
    QFileInfoList files;
    if (exists()) {
        if (directory == "")
            directory = baseCatalog;
        this->cd(directory);
        files = this->entryInfoList(QDir::Files);
        QStringList list = this->entryList(QDir::NoDotAndDotDot | QDir::Dirs);
        for (const QString &dir : list)
        {
            files.append(this->getFileList(directory + "\\" + dir));
        }
        this->cd(baseCatalog);
    }

    return files;
}

void CatalogManager::updateSyffixMap()
{
    syffixMap.clear();
    for (const QFileInfo& file : files)
        if (syffixMap.contains(file.suffix()))
            syffixMap.insert(file.suffix(),syffixMap.constFind(file.suffix()).value() + file.size() );//syffixMap.find(file.suffix()).value() + file.size());
        else
            syffixMap.insert(file.suffix(),file.size());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CatalogManager::refreshDir(QString string)
{
    if (string != "") {
        baseCatalog = string;
        this->cd(string);
    }
    this->refresh();
    files = getFileList();
    this->updateSyffixMap();
}

int CatalogManager::countFiles() const
{
    return files.size();
}

int CatalogManager::countFiles(QString syffix) const
{
    int count = 0;
    for (const QFileInfo& file : files)
        if (file.suffix() == syffix)
            count++;
    return count;
}

qint64 CatalogManager::directorySize() const
{
    qint64 size = 0;
    for (const QFileInfo& file : files)
            size += file.size();
    return size;
}

qint64 CatalogManager::directorySize(QString syffix) const
{
    /*
    qint64 size = 0;
    for (const QFileInfo& file : files)
        if (file.suffix() == syffix)
            size += file.size();
    return size;
    */
    return syffixMap.find(syffix).value();
}

QList<QString> CatalogManager::getSyffix() const
{
    return syffixMap.keys();
}

