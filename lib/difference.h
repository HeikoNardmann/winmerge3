#ifndef DIFFERENCE_H
#define DIFFERENCE_H

#include <QString>

#include "xdiffmmfile.h"
#include "differenceblock.h"

#include <vector>

class Difference
{
public:
    Difference(void);
    ~Difference();

    void Create(XDiffMmFile &side1, XDiffMmFile &side2);

private:
    static int StaticCallback(/*Difference*/void *instance, mmbuffer_t *mmBuf, int mmBufCnt);
    int Callback(mmbuffer_t *mmBuf, int mmBufCnt);

    QString side1FileName_, side2FileName_; //TODO: QFiles instead?
    std::vector<DifferenceBlock> blocks_;
};

#endif // DIFFERENCE_H
