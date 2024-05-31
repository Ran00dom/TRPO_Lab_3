#ifndef CALCULATORDIRSIZE_H
#define CALCULATORDIRSIZE_H

#include "calculatedirectory.h"

class CalculatorDirSize
{
public:
    CalculatorDirSize(CalculateDirectory* method):method(method) {}
    QMap<QString, qint64> calculate(QString directory) {
        return method->calculate(directory);
    }
    void setCalculate(CalculateDirectory* ptrmethod) {
        this->method = ptrmethod;
    }
private:
    CalculateDirectory* method;
};

#endif // CALCULATORDIRSIZE_H
