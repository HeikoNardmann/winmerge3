#include <iostream>
#include <sstream>
#include <stdexcept>
#include <stdlib.h>

#include <QFile>

#include "xdiff.h"

int const MmBlockSize = 256;

void *wrap_malloc(void *priv, unsigned int size)
{
    return malloc(size);
}

void wrap_free(void *priv, void *ptr)
{
    free(ptr);
}

void *wrap_realloc(void *priv, void *ptr, unsigned int size)
{
    return realloc(ptr, size);
}

void libxdiff_tools_init(void)
{
    memallocator_t malt;

    malt.priv = NULL;
    malt.malloc = wrap_malloc;
    malt.free = wrap_free;
    malt.realloc = wrap_realloc;
    xdl_set_allocator(&malt);
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
    QFile f2(argv[2]);
    qint64 f2Size = f2.size();
    mmfile_t f2Mm;
    success = xdl_init_mmfile(&f2Mm, MmBlockSize, XDL_MMF_ATOMIC);
    if (success != 0) { throw std::runtime_error("unable to create mm file for [" + f2.fileName().toStdString() + ']'); }

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

    xdl_free_mmfile(&f1Mm);
    xdl_free_mmfile(&f2Mm);

    }
    catch (std::exception &x)
    {
        std::cerr << "yo' mamma's error: " << x.what() << std::endl;
    }

    return 0;
}

