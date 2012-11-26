#ifndef XDIFFMMFILE_H
#define XDIFFMMFILE_H

#include <QString>

#include "xdiff.h"

#include <boost/utility.hpp>

class XDiffMmFile : boost::noncopyable
{
public:
    explicit XDiffMmFile(QString const &fileName);
    ~XDiffMmFile();

    QString FileName(void) const { return fileName_; }
    mmfile_t *MmFile(void) { return &mmfile_; }

private:
    void Load(void);

    QString fileName_;
    mmfile_t mmfile_;
};

#endif // XDIFFMMFILE_H
