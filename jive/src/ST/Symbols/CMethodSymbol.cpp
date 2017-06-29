#include "CMethodSymbol.h"

namespace ST
{

CVariableSymbol *CMethodSymbol::lookupArgument( CSymbol *symbol ) {
	for( auto argument : arguments ) {
        if( argument->getString() == symbol->getString() ) {
            return argument;
        }
    }

    return nullptr;
}

CVariableSymbol *CMethodSymbol::lookupVariable( CSymbol *symbol ) {
    for( auto variable : variables ) {
        if( variable->getString() == symbol->getString() ) {
            return variable;
        }
    }

    return nullptr;
}

}