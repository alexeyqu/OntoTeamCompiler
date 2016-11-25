#include "CCompoundExpression.h"

CCompoundExpression::CCompoundExpression( IExpression *_leftExpression, IExpression *_rightExpression, IType *_type ) : \
	leftExpression( _leftExpression ), rightExpression( _rightExpression ), type( _type ) {}

void CCompoundExpression::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}

IType *CCompoundExpression::getType() {
    return type;
}