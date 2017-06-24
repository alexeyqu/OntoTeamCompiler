#pragma once

#include <string>
#include "IVisitorTarget.h"
#include "CSymbol.h"

namespace AST 
{

class IType : public IVisitorTarget 
{
protected:
	IType( jive::TType _type ) : type( _type ) {}
public:
	jive::TType type;

	virtual CSymbol getSymbol() = 0;	
};

}