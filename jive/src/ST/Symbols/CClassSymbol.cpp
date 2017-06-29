#include "CClassSymbol.h"

namespace ST
{

CMethodSymbol *CClassSymbol::lookupMethod( CSymbol *method ) {
	for( auto method : methods ) {
        if( method->getString() == method->getString() ) {
            return method;
        }
    }

    return nullptr;
}

CVariableSymbol *CClassSymbol::lookupField( CSymbol *field ) {
    for( auto field : fields ) {
        if( field->getString() == field->getString() ) {
            return field;
        }
    }

    return nullptr;
}

}