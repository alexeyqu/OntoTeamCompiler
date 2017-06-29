#pragma once

#include "IExp.h"

namespace IRT
{

class CMEM : public IExp
{
public:
    CMEM( IExp *_exp ) : exp( _exp ) {}

    void Accept( IIRTVisitor *visitor ) { visitor->Visit( this ); }

    IExp *getExp() const { return exp; }

private:
    IExp *exp;
};

}