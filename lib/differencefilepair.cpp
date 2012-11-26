#include "differencefilepair.h"

#include "xdiffmmfile.h"

DifferenceFilePair::DifferenceFilePair(const QString &side1Name, const QString &side2Name)
    : side1Name_(side1Name)
    , side2Name_(side2Name)
{
    //complete
}
DifferenceFilePair::~DifferenceFilePair()
{
    //complete
}

Comparison DifferenceFilePair::DoCompare(void)
{
    XDiffMmFile file1(side1Name_);
    XDiffMmFile file2(side2Name_);

    int xdiffResult = xdl_mmfile_cmp(file1.MmFile(), file2.MmFile());
    Comparison result;
    result.name1 = side1Name_;
    result.name2 = side2Name_;
    result.result = (xdiffResult == 0) ? Comparison::Identical : Comparison::Different;
    return result;
}

Difference DifferenceFilePair::CreateDifference(void)
{
    XDiffMmFile file1(side1Name_);
    XDiffMmFile file2(side2Name_);
    Difference diff;
    diff.Create(file1, file2);
    return diff;
}
