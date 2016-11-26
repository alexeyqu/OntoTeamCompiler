#pragma once

#include <map>
#include <vector>
#include "ISymbol.h"
#include "CVariableSymbol.h"

class CMethodSymbol : public ISymbol {

public:
	CMethodSymbol( std::string _name, IType* _type ) : ISymbol( _name, _type ) {}

	std::vector<IType*> argumentTypes;
	std::map<std::string, CVariableSymbol*> arguments;
	std::map<std::string, CVariableSymbol*> variables;
}; 
