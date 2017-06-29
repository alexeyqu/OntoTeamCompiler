#include "CJiveEnvironment.h"

namespace jive 
{

CJiveEnvironment::CJiveEnvironment() : symbolTable( new CSymbolTable() ), typeMap( new ST::CTypeMap() ), classMap( new ST::CClassMap() ) {
	// for( int i = 0; i < jive::keywords.size(); i++ ) {
    //     symbolTable->insert( jive::keywords[i] );
    // }
}

}