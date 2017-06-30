#pragma once

#include "IExp.h"

namespace IRT
{

class CExpList : public IExp
{
public:
    CExpList( IExp *_exp, CExpList *_next ) : exp( _exp ), next( _next ) {}
    CExpList( IExp *_exp ) : exp( _exp ), next( nullptr ) {}

    void Accept( IIRTVisitor *visitor ) { visitor->Visit( this ); }

    const IExp *getExp() const { return exp; }
    const CExpList *getNext() const { return next; }

private:
    IExp *exp;
    CExpList *next;
};

}