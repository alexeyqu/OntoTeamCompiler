#pragma once

#include "IStm.h"

namespace IRT
{

class CStmList : public IStm
{
public:
    CStmList( IStm *_stm, CStmList *_next ) : stm( _stm ), next( _next ) {}
    CStmList( IStm *_stm ) : stm( _stm ), next( nullptr ) {}

    void Accept( IIRTVisitor *visitor ) { visitor->Visit( this ); }

    IStm *getStm() const { return stm; }
    CStmList *getNext() const { return next; }

private:
    IStm *stm;
    CStmList *next;
};

}