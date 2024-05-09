#include "catalogmanager.h"
#include <QCoreApplication>
#include <QDir>
#include <iostream>
#include <QDebug>
#include <QMap>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    /*
    QDir fgd("C:\\lab1");
    QStringList list = fgd.entryList(QDir::NoDotAndDotDot | QDir::Dirs);
    for(const QString &str : list)
    {
        qDebug() << str;
    }

    QFileInfoList list_info = fgd.entryInfoList(QDir::Filter::Files);
    for(const QFileInfo &file : list_info)
    {
        qDebug() << file.suffix();
    }
*/
    CatalogManager manager("C:\\lab1");
    std::string string;

    std::cout << "<Directory command>" << std::endl;
    std::cout << "syffix" << std::endl;
    std::cout << "size" << std::endl;
    std::cout << "count" << std::endl;

    while (true)
    {
        std::cout << "Enter directory or 'exit'" << std::endl;
        std::cin >> string;

        if (string == "exit")
            a.exit();
        if (string == "")
            manager.refreshDir(string.c_str());
        std::cout << "Enter command" << std::endl;
        std::cin >> string;
        if (string == "count")
            qDebug() << manager.countFiles();
        if (string == "size")
            qDebug() << manager.directorySize();
        if (string == "syffix")
            qDebug() << manager.getSyffix();
        if (string == "exit")
            a.exit();

    }


    return a.exec();
}
