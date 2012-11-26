#ifndef COMPARISON_H
#define COMPARISON_H

#include <QString>

struct Comparison
{
public:
    enum Code
    {
        Identical = 0,
        Different
    };
    QString name1, name2;
    Code result;
};

#endif // COMPARISON_H
