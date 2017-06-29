#pragma once

#include "IExp.h"
#include "IStm.h"

namespace IRT
{

class CMOVE : public IStm
{
public:
    CMOVE( IExp *_dst, IExp *_src ) : dst( _dst ), src( _src ) {}

    void Accept( IIRTVisitor *visitor ) { visitor->Visit( this ); }

    IExp *getDst() const { return dst; }
    IExp *getSrc() const { return src; }

private:
    IExp *dst;
    IExp *src;
};

}