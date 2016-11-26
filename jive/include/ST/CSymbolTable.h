#pragma once

#include <string>
#include <map>
#include <vector>
#include "CSymbols.h"

class CSymbolTable {
public:
	bool Add( CClassSymbol* symbol );
	ISymbol* FindMethod( std::string& className, std::string& mehodName );
	ISymbol* FindVariable( std::string& className, std::string& mehodName, std::string& varName );

	std::map<std::string, CClassSymbol*> table;
};