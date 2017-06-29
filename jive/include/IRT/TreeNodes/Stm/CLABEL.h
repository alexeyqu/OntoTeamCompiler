#pragma once

#include "IStm.h"
#include "CLabel.h"

namespace IRT
{

class CLABEL : public IStm
{
public:
	CLABEL( CLabel* _label ) : label( _label ) {};

    void Accept( IIRTVisitor *visitor ) { visitor->Visit( this ); }

	CLabel* getLabel() const { return label; }

private:
	CLabel* label;
};

}


