#pragma once

#include "IExp.h"
#include "IStm.h"

namespace IRT
{

class CESEQ : public IExp
{
public:
    CESEQ( IExp *_exp, IStm *_stm ) : exp( _exp ), stm( _stm ) {}

    void Accept( IIRTVisitor *visitor ) { visitor->Visit( this ); }

    IExp *getExp() const { return exp; }
    IStm *getStm() const { return stm; }

private:
    IExp *exp;
    IStm *stm;
};

}