#include "CSymbolTable.h"

void CSymbolTable::insert( std::string name ) {
    CSymbol *newSymbol = new CSymbol( name );
    table.insert( *newSymbol ); 
}