#pragma once

#include "IExp.h"

namespace IRT
{

class IExpList : public IExp
{
public:
    IExpList( IExp *_exp, IExpList *_next ) : exp( _exp ), next( _next ) {}
    IExpList( IExp *_exp ) : exp( _exp ), next( nullptr ) {}

    void Accept( IIRTVisitor *visitor ) { visitor->Visit( this ); }

    const IExp *getExp() const { return exp; }
    const IExpList *getNext() const { return next; }

private:
    IExp *exp;
    IExpList *next;
};

}