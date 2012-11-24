#ifndef DIFFERENCEFILEPAIR_H
#define DIFFERENCEFILEPAIR_H

#include "differencefile.h"

#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>

class DifferenceFilePair : boost::noncopyable
{
public:
    typedef boost::shared_ptr<DifferenceFilePair> holder_t;

//    DifferenceFilePair(DifferenceFile::holder_t const &side1, DifferenceFile::holder_t const &side2);
    DifferenceFilePair(QString const &side1FileName, QString const &side2FileName);
    ~DifferenceFilePair();

private:
    DifferenceFile side1_, side2_;
};

#endif // DIFFERENCEFILEPAIR_H
