#ifndef CALCULATEDIRECTORY_H
#define CALCULATEDIRECTORY_H

#include <QDir>
#include <QMap>

class CalculateDirectory : public QDir
{
public:
    CalculateDirectory():QDir() {}
    virtual QMap<QString, qint64> calculate(QString directory, QString mapCatalog = "", int level = 0) = 0;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CalculateTypeSize : public CalculateDirectory
{
public:
    CalculateTypeSize():CalculateDirectory() {}
    virtual QMap<QString, qint64> calculate(QString directory, QString mapCatalog, int level);
};



class CalculateFolderSize : public CalculateDirectory
{
public:
    CalculateFolderSize():CalculateDirectory() {};
    virtual QMap<QString, qint64> calculate(QString directory, QString mapCatalog, int level);
};


#endif // CALCULATEDIRECTORY_H
