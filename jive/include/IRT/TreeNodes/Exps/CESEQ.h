#pragma once

#include "IExp.h"
#include "IStm.h"

namespace IRT
{

class CESEQ : public IExp
{
public:
    CESEQ( IStm *_stm, IExp *_exp ) : stm( _stm ), exp( _exp ) {}

    void Accept( IIRTVisitor *visitor ) { visitor->Visit( this ); }

    IExp *getExp() const { return exp; }
    IStm *getStm() const { return stm; }

private:
    IExp *exp;
    IStm *stm;
};

}