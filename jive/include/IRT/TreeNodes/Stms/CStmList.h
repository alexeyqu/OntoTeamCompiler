#pragma once

#include "IStm.h"

namespace IRT
{

class IStmList : public IStm
{
public:
    IStmList( IStm *_stm, IStmList *_next ) : stm( _stm ), next( _next ) {}
    IStmList( IStm *_stm ) : stm( _stm ), next( nullptr ) {}

    void Accept( IIRTVisitor *visitor ) { visitor->Visit( this ); }

    const IStm *getStm() const { return stm; }
    const IStmList *getNext() const { return next; }

private:
    IStm *stm;
    IStmList *next;
};

}