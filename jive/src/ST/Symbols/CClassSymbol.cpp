#include "CClassSymbol.h"

namespace ST
{

CMethodSymbol *CClassSymbol::lookupMethod( CMethod *method ) {
	for( auto methodSymbol : methods ) {
		if( methodSymbol->vertexAST == method ) {
			return methodSymbol;
		}
	}

	return nullptr;
}

CVariableSymbol *CClassSymbol::lookupField( CVariable *variable ) {
	for( auto fieldSymbol : fields ) {
		if( fieldSymbol->vertexAST == variable ) {
			return fieldSymbol;
		}
	}

	return nullptr;
}

}