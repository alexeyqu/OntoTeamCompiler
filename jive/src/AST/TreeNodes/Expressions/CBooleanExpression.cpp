#include "CBooleanExpression.h"

namespace AST 
{

CBooleanExpression::CBooleanExpression( bool _value ) : value( _value ) {}

void CBooleanExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

}