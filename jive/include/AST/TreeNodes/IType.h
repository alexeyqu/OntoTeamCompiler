#pragma once

#include <string>
#include "IVisitorTarget.h"

class IType : public IVisitorTarget 
{
protected:
	IType( jive::TType _type ) : type( _type ) {}
public:
	jive::TType type;

	// virtual getSymbol() = 0;	
};