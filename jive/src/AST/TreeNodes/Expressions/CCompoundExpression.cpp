
#include "CCompoundExpression.h"

namespace AST 
{

CCompoundExpression::CCompoundExpression( IExpression *_leftExpression, IExpression *_rightExpression ) : \
	leftExpression( _leftExpression ), rightExpression( _rightExpression ) {}

void CCompoundExpression::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}

}