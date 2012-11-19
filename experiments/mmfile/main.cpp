#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>

#include <boost/bind.hpp>

#include <QFile>

#include "common.h"
#include "xdiff.h"

int main(int argc, char *argv[])
{
    try {

    if (argc < 2) { throw std::runtime_error("missing arguments"); }

    libxdiff_tools_init();

    QFile file(argv[1]);

    mmfile_t fMm;
    int success = xdl_init_mmfile(&fMm, MmBlockSize, 0/*XDL_MMF_ATOMIC*/);
    if (success != 0) { throw std::runtime_error("unable to create mm file"); }
    CleanUp freeMm(boost::bind(&xdl_free_mmfile, &fMm));

    qint64 fileSize = file.size();
    std::cout << "file size is " << fileSize << std::endl;
    file.open(QIODevice::ReadOnly);
    long bytesRead = xdl_write_mmfile(&fMm, file.readAll().constData(), fileSize);
    std::cout << "bytes read is " << bytesRead << std::endl;
    bool isCompact = (xdl_mmfile_iscompact(&fMm) == 0) ? false : true;
    std::cout << "memory file is " << ((isCompact) ? "" : "NOT ") << "compact" << std::endl;

    long blockSize = 0;
    unsigned int blockCnt = 0;
    void *dummy = xdl_mmfile_first(&fMm, &blockSize);
    while (dummy)
    {
        std::cout << "block #" << (++blockCnt) << " is " << blockSize << " bytes" << std::endl;
        dummy = xdl_mmfile_next(&fMm, &blockSize);
    }   //while

    }
    catch (std::exception const &x)
    {
        std::cerr << "error: " << x.what() << std::endl;
        return -1;
    }
    return 0;
}
