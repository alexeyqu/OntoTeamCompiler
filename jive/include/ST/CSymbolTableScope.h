#pragma once

#include <string>
#include <map>
#include "ISymbol.h"

class CSymbolTableScope {
public:
	CSymbolTableScope();

	void Add(ISymbol* symbol);
	ISymbol* Lookup( std::string& name );
	ISymbol* Lookup( std::string& name, CSymbolTableScope*& retScope);

	std::map<std::string::name, ISymbol*> table;
};