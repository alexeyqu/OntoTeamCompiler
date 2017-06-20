#include "CIdExpression.h"

CIdExpression::CIdExpression( CSymbol *_name ) : \
	name( _name ) {}

void CIdExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

flyweight<std::string> CIdExpression::getName() const {
	return name->get();
}