#pragma once

#include "IExp.h"

namespace IRT
{

class CCONST : public IExp
{
public:
    CCONST( int _value ) : value( _value ) {}

    void Accept( IIRTVisitor *visitor ) { visitor->Visit( this ); }

    int getValue() const { return value; }

private:
    int value;
};

}