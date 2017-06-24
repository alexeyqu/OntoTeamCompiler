#include "CNewIntArrayExpression.h"

namespace AST 
{

CNewIntArrayExpression::CNewIntArrayExpression( IExpression *_arrSize ) : arrSize( _arrSize ) {}

void CNewIntArrayExpression::Accept( IVisitor *visitor ) {
	visitor->Visit( this );
}

}