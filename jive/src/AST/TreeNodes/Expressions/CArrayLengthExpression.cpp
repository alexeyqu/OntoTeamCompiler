#include "CArrayLengthExpression.h"

CArrayLengthExpression::CArrayLengthExpression( IExpression *_exp ) : exp( _exp ) {}

void CArrayLengthExpression::Accept( IVisitor *visitor ) {
    visitor->Visit( this );
}
