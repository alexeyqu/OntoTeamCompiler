#include "CJiveEnvironment.h"

namespace jive 
{

CJiveEnvironment::CJiveEnvironment() : symbolTable( new CSymbolTable() ), typeTable( new CTypeTable() ) {
	for( int i = 0; i < jive::keywords.size(); i++ ) {
        symbolTable->insert( jive::keywords[i] );
    }

    for( int i = jive::INTEGER; i < jive::_LastType; i++ ) {
        typeTable->insert( new CBuiltInType( static_cast<jive::TType>( i ) ), new CTypeSymbol( new CSymbol( "builtin" ) ) );
    }
}

}