#include "CJiveEnvironment.h"

namespace jive 
{

CJiveEnvironment::CJiveEnvironment() : symbolTable( new CSymbolTable() ) {
	for( int i = 0; i < jive::keywords.size(); i++ ) {
        symbolTable->insert( jive::keywords[i] );
    }
}

}