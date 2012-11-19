#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>

#include <boost/bind.hpp>
#include <boost/function.hpp>

#include <QFile>

#include "common.h"
#include "xdiff.h"

int outf(void*, mmbuffer_t *mmBuf, int mmBufCnt)
{
    for (int idx = 0; idx < mmBufCnt; ++idx)
    {
        mmbuffer_t const &buf = *(mmBuf+idx);
        std::copy(buf.ptr, buf.ptr + buf.size, std::ostream_iterator<char>(std::cout));
    }
    return 0;
}

int main(int argc, char *argv[])
{
    try {

    if (argc < 3) { throw std::runtime_error("missing arguments"); }

    libxdiff_tools_init();

    QFile f1(argv[1]);
    qint64 f1Size = f1.size();
    mmfile_t f1Mm;
    int success = xdl_init_mmfile(&f1Mm, MmBlockSize, XDL_MMF_ATOMIC);
    if (success != 0) { throw std::runtime_error("unable to create mm file for [" + f1.fileName().toStdString() + ']'); }
    CleanUp freeF1(boost::bind(&xdl_free_mmfile, &f1Mm));

    QFile f2(argv[2]);
    qint64 f2Size = f2.size();
    mmfile_t f2Mm;
    success = xdl_init_mmfile(&f2Mm, MmBlockSize, XDL_MMF_ATOMIC);
    if (success != 0) { throw std::runtime_error("unable to create mm file for [" + f2.fileName().toStdString() + ']'); }
    CleanUp freeF2(boost::bind(&xdl_free_mmfile, &f2Mm));

    char *data1 = static_cast<char*>(xdl_mmfile_writeallocate(&f1Mm, f1Size));
    if (data1 == NULL)
    {
        std::ostringstream msg;
        msg << "unable to allocate [" << f1Size << "] bytes for [" << f1.fileName().toStdString() << "] mm file";
        throw std::runtime_error(msg.str());
    }
    char *data2 = static_cast<char*>(xdl_mmfile_writeallocate(&f2Mm, f2Size));
    if (data2 == NULL)
    {
        std::ostringstream msg;
        msg << "unable to allocate [" << f2Size << "] bytes for [" << f2.fileName().toStdString() << "] mm file";
        throw std::runtime_error(msg.str());
    }

    f1.open(QIODevice::ReadOnly);
    memcpy(data1, f1.readAll().constData(), static_cast<size_t>(f1Size));
    f1.close();

    f2.open(QIODevice::ReadOnly);
    memcpy(data2, f2.readAll().constData(), static_cast<size_t>(f2Size));
    f2.close();

    xpparam_t parms; parms.flags = 0;   //no flags
    xdemitconf_t ctx; ctx.ctxlen = 3;
    xdemitcb_t cb; cb.priv = NULL; cb.outf = &outf;
    success = xdl_diff(&f1Mm, &f2Mm, &parms, &ctx, &cb);
    if (success != 0) { throw std::runtime_error("unable to generate diff between [" + f1.fileName().toStdString() + "] and [" + f2.fileName().toStdString() + ']'); }

    }
    catch (std::exception &x)
    {
        std::cerr << "error: " << x.what() << std::endl;
    }
    return 0;
}
