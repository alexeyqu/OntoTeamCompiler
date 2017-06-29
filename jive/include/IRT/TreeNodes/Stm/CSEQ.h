#pragma once

#include "IStm.h"

namespace IRT
{

class CSEQ : public IStm
{
public:
    CSEQ( IStm *_left, IStm *_right ) : left( _left ), right( _right ) {}

    void Accept( IIRTVisitor *visitor ) { visitor->Visit( this ); }

    IStm *getLeft() const { return left; }
    IStm *getRight() const { return right; }

private:
    IStm *left;
    IStm *right;
};

}