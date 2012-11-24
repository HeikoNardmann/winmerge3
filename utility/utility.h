#ifndef UTILITY_H
#define UTILITY_H

#include <boost/function.hpp>

namespace utility {

class CleanUp
{
public:
    typedef boost::function<void(void)> cleanup_t;
    CleanUp(cleanup_t const &cleanup) : cleanup_(cleanup) {}
    ~CleanUp(void) { cleanup_(); }
private:
    cleanup_t cleanup_;
};

}   //namespace utility

#endif  //UTILITY_H
