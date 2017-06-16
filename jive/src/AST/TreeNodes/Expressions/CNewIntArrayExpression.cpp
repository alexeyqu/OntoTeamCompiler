#include "CNewIntArrayExpression.h"

CNewIntArrayExpression::CNewIntArrayExpression( IExpression *_arrSize ) : arrSize( _arrSize ) {}

void CNewIntArrayExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}