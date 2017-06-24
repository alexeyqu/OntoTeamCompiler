#pragma once

#include <vector>
#include "CVariableSymbol.h"
#include "ISymbol.h"

namespace ST
{

class CMethodSymbol : public ISymbol
{
public:
    CMethodSymbol( CTypeSymbol *_type, CSymbol *_name ) : type( _type ), name( _name ), arguments(), localVars() {}

	std::vector<CVariableSymbol *> arguments;
	std::vector<CVariableSymbol *> localVars;
};

}