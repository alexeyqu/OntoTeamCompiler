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

    const IStm *getStm() const { return stm; }
    const CStmList *getNext() const { return next; }

private:
    IStm *stm;
    CStmList *next;
};

}