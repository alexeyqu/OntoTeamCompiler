#include "AST/TreeNodes/Expressions/CIdExpression.h"

CIdExpression::CIdExpression( const char *_name ) : \
	name( _name ) {}

void CIdExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}