#include "CSymbolTable.h"

namespace ST 
{

void CSymbolTable::insert( std::string name ) {
    table.insert( CSymbol( name ) ); 
}

}