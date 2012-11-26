#ifndef DIFFERENCEFILEPAIR_H
#define DIFFERENCEFILEPAIR_H

#include <QString>

#include "comparison.h"
#include "difference.h"

class DifferenceFilePair
{
public:
    DifferenceFilePair(QString const &side1Name, QString const &side2Name);
    ~DifferenceFilePair();

    QString GetFile1Name(void) const { return side1Name_; }
    QString GetFile2Name(void) const { return side2Name_; }

    Comparison DoCompare(void);
    Difference CreateDifference(void);

private:
    QString side1Name_, side2Name_;
};

#endif // DIFFERENCEFILEPAIR_H
