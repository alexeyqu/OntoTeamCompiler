#pragma once

#include "IExp.h"

namespace IRT
{

class CEXP : public IStm
{
public:
    CEXP( IExp *_exp ) : exp( _exp ) {}

    void Accept( IIRTVisitor *visitor ) { visitor->Visit( this ); }

    IExp *getExp() const { return exp; }

private:
    IExp *exp;
};

}