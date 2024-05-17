#include "calculatedirectory.h"
#include <QCoreApplication>
#include <QDir>
#include <cmath>
#include <iostream>
#include <QDebug>
#include <QMap>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string string;

    QMap<QString, qint64> map;
    CalculateDirectory* calc;
    bool flag = 0;
    while (true) {
        std::cout << "Select strategy: 'folder' , 'type' " << std::endl;
        std::cin >> string;
        if (string == "folder") {
            calc = new CalculateFolderSize;
            flag = 1;
        }
        if (string == "type") {
            calc = new CalculateTypeSize;
            flag = 1;
        }

        if (flag) {
            flag = 0;
            std::cout << "Enter directory" << std::endl;
            std::cin >> string;
            map = calc->calculate(string.c_str());

            qint64 size = 0;
            foreach (const qint64 value, map.values())
                size += value;
            qDebug() << "Map > " << map.values();
            qDebug() << Qt::endl;
            for (auto i = map.cbegin(), end = map.cend(); i != end; ++i)
            {
                if ((i.value() * 100000 / size) >= 10)
                    qDebug() << (i.key()) << ": " <<  round(((double)i.value() * 10000 / size))/100 << "%";
                else
                    qDebug() << (i.key()) << ": " <<  " < 0.01" << "%";
            }
            qDebug() << Qt::endl;
        }
    }
    return a.exec();
}
