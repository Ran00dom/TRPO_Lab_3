#ifndef CATALOGMANAGER_H
#define CATALOGMANAGER_H

#include <QDir>
#include <QMap>

class CatalogManager : public QDir {
private:
    QString baseCatalog;
    QFileInfoList files;
    QMap<QString, qint64> syffixMap;

    void updateSyffixMap();
    QMap<QString, qint64> resetFilesTypeMap();
    QFileInfoList getFileList(QString directory = "");
public:
    CatalogManager(const QString &path);
    void refreshDir(QString string = "");
    qint64 directorySize() const;
    qint64 directorySize(QString syffix) const;
    int countFiles() const;
    int countFiles(QString syffix) const;

    QList<QString> getSyffix() const;
};

#endif // CATALOGMANAGER_H
