#include "CSymbolTable.h"

namespace AST 
{

void CSymbolTable::insert( std::string name ) {
    CSymbol *newSymbol = new CSymbol( name );
    table.insert( *newSymbol ); 
}

}