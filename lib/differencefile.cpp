#include <QFile>

#include "differencefile.h"

#include <stdexcept>

long const MmBlockSize = 8 * 1024;  //TODO: optimal value?

DifferenceFile::DifferenceFile(QString const &fileName)
    :   fileName_(fileName)
{
    int success = xdl_init_mmfile(&mmfile_, MmBlockSize, XDL_MMF_ATOMIC);
    if (success != 0) { throw std::runtime_error("unable to create memory file"); }
}
DifferenceFile::~DifferenceFile()
{
    xdl_free_mmfile(&mmfile_);
}

void DifferenceFile::Load(void)
{
    QFile file(fileName_);
    qint64 size = file.size();
    char *data = xdl_mmfile_writeallocate(&mmfile_, static_cast<long>(size));
    if (data == NULL)
    {
        std::ostringstream msg;
        msg << "for " << fileName_ << ", unable to allocate " << size << " bytes for memory file";
        throw std::runtime_error(msg.str());
    }
    file.open(QIODevice::ReadOnly);
    qint64 rslt = file.read(data, size);
    file.close();

    if (rslt < 0)
    {
        std::ostringstream msg;
        msg << "unable to read " << fileName_ << " into memory file";
        throw std::runtime_error(msg.str());
    }
}
