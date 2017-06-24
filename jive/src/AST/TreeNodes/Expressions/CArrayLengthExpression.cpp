#include "CArrayLengthExpression.h"

namespace AST 
{

CArrayLengthExpression::CArrayLengthExpression( IExpression *_exp ) : exp( _exp ) {}

void CArrayLengthExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

}