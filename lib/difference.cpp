#include "difference.h"

#include "xdiff.h"

#include <sstream>
#include <stdexcept>

/*--------------------------------- public ----------------------------------*/
Difference::Difference(void)
{
}

Difference::~Difference()
{
}

void Difference::Create(XDiffMmFile &side1, XDiffMmFile &side2)
{
    xpparam_t parms; parms.flags = 0;   //no flags
    xdemitconf_t ctx; ctx.ctxlen = 0;   //no context, just the difference
    xdemitcb_t cb; cb.priv = this; cb.outf = &Difference::StaticCallback;
    int xdiffResult = xdl_diff(side1.MmFile(), side2.MmFile(), &parms, &ctx, &cb);
    if (xdiffResult != 0)
    {
        std::ostringstream msg;
        msg << "unable to generate diff between [" << side1.FileName().toStdString()
            << "] and [" << side2.FileName().toStdString() << ']';
        throw std::runtime_error(msg.str());
    }
}

/*--------------------------------- private ---------------------------------*/
/*static*/ int Difference::StaticCallback(void *instance, mmbuffer_t *mmBuf, int mmBufCnt)
{
    return static_cast<Difference*>(instance)->Callback(mmBuf, mmBufCnt);
}

int Difference::Callback(mmbuffer_t *mmBuf, int mmBufCnt)
{
    //TODO: WRITEME
    return 0;
}
