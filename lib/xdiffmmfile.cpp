#include <QFile>

#include "xdiffmmfile.h"

#include <sstream>
#include <stdexcept>

/*-------------------------------- internal ---------------------------------*/
long const MmBlockSize = 8 * 1024;  //TODO: optimal value?

/*--------------------------------- public ----------------------------------*/
XDiffMmFile::XDiffMmFile(QString const &fileName)
    :   fileName_(fileName)
{
    int success = xdl_init_mmfile(&mmfile_, MmBlockSize, XDL_MMF_ATOMIC);
    if (success != 0) { throw std::runtime_error("unable to create memory file"); }
    Load();
}

XDiffMmFile::~XDiffMmFile()
{
    xdl_free_mmfile(&mmfile_);
}

/*--------------------------------- private ---------------------------------*/
void XDiffMmFile::Load(void)
{
    QFile file(fileName_);
    qint64 size = file.size();
    char *data = static_cast<char*>(xdl_mmfile_writeallocate(&mmfile_, static_cast<long>(size)));
    if (data == NULL)
    {
        std::ostringstream msg;
        msg << "for " << fileName_.toStdString() << ", unable to allocate " << size << " bytes for memory file";
        throw std::runtime_error(msg.str());
    }
    file.open(QIODevice::ReadOnly);
    qint64 rslt = file.read(data, size);
    file.close();

    if (rslt < 0)
    {
        std::ostringstream msg;
        msg << "unable to read " << fileName_.toStdString() << " into memory file";
        throw std::runtime_error(msg.str());
    }
}
