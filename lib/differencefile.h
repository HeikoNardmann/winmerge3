#ifndef DIFFERENCE_FILE_H
#define DIFFERENCE_FILE_H

#include <QString>

#include "xdiff.h"

#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>

class DifferenceFile : boost::noncopyable
{
public:
    typedef boost::shared_ptr<DifferenceFile> holder_t;

    explicit DifferenceFile(QString const &fileName);
    ~DifferenceFile();

    QString FileName(void) const { return fileName_; }
    void Load(void);

private:
    QString fileName_;
    mmfile_t mmfile_;
};

#endif // DIFFERENCE_FILE_H
