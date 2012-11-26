#ifndef DIFFERENCEBLOCK_H
#define DIFFERENCEBLOCK_H

#include <qglobal.h>

#include "differenceline.h"

#include <vector>
//URHERE - How does DifferenceBlock (and DifferenceLine) obtain actual file content
//or how is it applied to file? lines_t probably needs to be shared_ptr<> since
//DifferenceBlocks go in collections and need to be cheap to copy. Use list<>
//instead of vector<>?
class DifferenceBlock
{
public:
    DifferenceBlock(quint64 start, quint64 length);

private:
    typedef std::vector<DifferenceLine> lines_t;
    quint64 start_, length_;
    lines_t lines_;
};

#endif // DIFFERENCEBLOCK_H
