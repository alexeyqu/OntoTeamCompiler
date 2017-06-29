#pragma once

#include "IExp.h"
#include "CExpList.h"

namespace IRT
{

class CCALL : public IExp
{
public:
    CCALL( IExp *_func, CExpList *_args ) : func( _func ), args( _args ) {}

    void Accept( IIRTVisitor *visitor ) { visitor->Visit( this ); }

    IExp *getFunc() const { return func; }
    CExpList *getArgs() const { return args; }

private:
    IExp *func;
    CExpList *args;
};

}