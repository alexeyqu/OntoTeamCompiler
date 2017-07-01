#pragma once

#include "IStm.h"
#include "IExp.h"
#include "CLabelList.h"

namespace IRT
{

class CJUMP : public IStm
{
public:
    CJUMP( IExp *_exp, CLabelList *_targets) : exp( _exp ), targets( _targets ) {}
    CJUMP( CLabel* label ) : exp( new CNAME( label ) ), targets( new CLabelList( label ) ) {}

    void Accept( IIRTVisitor *visitor ) { visitor->Visit( this ); }

    IExp *getExp() const { return exp; }
    CLabelList *getTargets() const { return targets; }

private:
    IExp *exp;
    CLabelList *targets;
};

}