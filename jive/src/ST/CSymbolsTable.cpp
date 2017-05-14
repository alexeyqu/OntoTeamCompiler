#include "ST/CSymbolsTable.h"
#include "ST/CSymbols.h"
#include <cassert>

bool CSymbolsTable::AddClass( CClassSymbol* symbol ) {
	assert( symbol );
	if ( declaredClasses.GetObject( symbol->name ) ) {
		return false;
	}
	declaredClasses.InsertObject( symbol->name, symbol );
	return true;
}

CClassSymbol* CSymbolsTable::GetClassByName( const std::string& className ) {
	return declaredClasses.GetObject( CSymbol::GetSymbol( className ) );
}

CClassSymbol* CSymbolsTable::GetClassByName( CSymbol* symbol ) {
	return declaredClasses.GetObject( symbol );
}
