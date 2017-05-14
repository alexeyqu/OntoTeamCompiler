#include "AST/TreeNodes/Expressions/CBooleanExpression.h"

CBooleanExpression::CBooleanExpression( bool _value ) : value( _value ) {}

void CBooleanExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}
