#include "CIdExpression.h"

CIdExpression::CIdExpression( const char *_name ) : \
	name( _name ), type( enums::IDENTIFIER ) {}

void CIdExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

enums::TType CIdExpression::getType() {
	return symbolTable.Lookup(this)->type->type;
}