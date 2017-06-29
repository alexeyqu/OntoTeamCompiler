#include "CClassSymbol.h"

namespace ST
{

CMethodSymbol *CClassSymbol::lookupMethod( CSymbol *symbol ) {
	for( auto method : methods ) {
        if( method->getString() == symbol->getString() ) {
            return method;
        }
    }

    return nullptr;
}

CVariableSymbol *CClassSymbol::lookupField( CSymbol *symbol ) {
    for( auto field : fields ) {
        if( field->getString() == symbol->getString() ) {
            return field;
        }
    }

    return nullptr;
}

}