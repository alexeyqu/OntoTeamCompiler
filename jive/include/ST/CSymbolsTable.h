#pragma once

#include "CSymbol.h"
#include "ST/CSymbolStorage.h"

class CClassSymbol;
class CMethodSymbol;
class CVariableSymbol;

class CSymbolsTable {
public:
	CSymbolsTable() : declaredClasses() {};

	bool AddClass( CClassSymbol* classInfo );
	CClassSymbol* GetClassByName( const std::string& className );
	CClassSymbol* GetClassByName( CSymbol* symbol );

private:
	CSymbolStorage<CClassSymbol*> declaredClasses;
};