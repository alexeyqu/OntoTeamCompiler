#pragma once

#include <unordered_set>
#include "CVariableSymbol.h"
#include "ISymbol.h"

namespace ST
{

class CMethodSymbol : public ISymbol
{
public:
    CMethodSymbol( CSymbol *_name, CTypeSymbol *_type ) : ISymbol( _name, _type ), arguments(), variables() {}

	std::unordered_set<CVariableSymbol *> arguments;
	std::unordered_set<CVariableSymbol *> variables;
};

}