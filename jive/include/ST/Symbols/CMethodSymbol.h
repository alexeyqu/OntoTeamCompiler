#pragma once

#include <map>
#include <vector>
#include "../ISymbol.h"
#include "CVariableSymbol.h"
#include "ST/CSymbolStorage.h"

class CMethodSymbol : public ISymbol {

public:
	CMethodSymbol( std::string _name, IType* _type ) : ISymbol( _name, _type ) {}

	std::vector<IType*> argumentTypes;
	CSymbolStorage<CVariableSymbol*> arguments;
	CSymbolStorage<CVariableSymbol*> variables;
}; 
