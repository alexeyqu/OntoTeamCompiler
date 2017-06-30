#pragma once

namespace IRT
{

class CCJUMP
{
public:
    CCJUMP( TCJUMP _relop, IExp *_left, IExp *_right, CLabel *_ifTrue, CLabel *_ifFalse ) : \
        relop( _relop ), left( _left ), right( _right ), ifTrue( _ifTrue ), ifFalse( _ifFalse ) {}

    void Accept( IIRTVisitor *visitor ) { visitor->Visit( this ); }

    TCJUMP getRelop() const { return relop; }
    IExp *getLeft() const { return left; }
    IExp *getRight() const { return right; }
    CLabel *getIfTrue() const { return ifTrue; }
	CLabel *getIfFalse() const { return ifFalse; }

private:
    TCJUMP relop; 
    IExp *left;
    IExp *right;
    CLabel *ifTrue;
    CLabel *ifFalse;
};

}