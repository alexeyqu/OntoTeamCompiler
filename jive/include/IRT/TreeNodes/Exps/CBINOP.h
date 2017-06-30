#pragma once

#include "IExp.h"

namespace IRT
{

class CBINOP : public IExp
{
public:
    CBINOP( TBINOP _binop, IExp *_left, IExp *_right ) : binop( _binop ), left( _left ), right( _right ) {}

    void Accept( IIRTVisitor *visitor ) { visitor->Visit( this ); }

    TBINOP getBinop() const { return binop; }
    IExp *getLeft() const { return left; }
    IExp *getRight() const { return right; }

private:
    TBINOP binop;
    IExp *left;
    IExp *right;
};

}