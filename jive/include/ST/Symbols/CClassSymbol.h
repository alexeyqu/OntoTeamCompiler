#pragma once

#include <map>
#include "ISymbol.h"
#include "CMethodSymbol.h"
#include "CVariableSymbol.h"

class CClassSymbol : public ISymbol {

public:
	CClassSymbol( std::string _name, IType* _type ) : ISymbol( _name, _type ), parentName( "" ) {}

	std::string parentName;
	std::map<std::string, CVariableSymbol*> fields;
	std::map<std::string, CMethodSymbol*> methods;
}; 

