#pragma once

#include "IExp.h"
#include "CLabel.h"

namespace IRT
{

class CNAME : public IExp
{
public:
    CNAME( CLabel *_label ) : label( _label ) {}

    void Accept( IIRTVisitor *visitor ) { visitor->Visit( this ); }

    CLabel *getLabel() const { return label; }

private:
    CLabel *label;
};

}