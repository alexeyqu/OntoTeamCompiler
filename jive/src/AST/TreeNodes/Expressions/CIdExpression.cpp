#include "CIdExpression.h"

namespace AST 
{

CIdExpression::CIdExpression( CSymbol *_name ) : \
	name( _name ) {}

void CIdExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

flyweight<std::string> CIdExpression::getName() const {
	return name->get();
}

}