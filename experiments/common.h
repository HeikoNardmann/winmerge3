#ifndef COMMON_H
#define COMMON_H

#include <boost/function.hpp>

int const MmBlockSize = (1024*8);   //from xtestutils.c

void libxdiff_tools_init(void);

class CleanUp
{
public:
    typedef boost::function<void(void)> cleanup_t;
    CleanUp(cleanup_t const &cleanup) : cleanup_(cleanup) {}
    ~CleanUp(void) { cleanup_(); }
private:
    cleanup_t cleanup_;
};

#endif // COMMON_H
