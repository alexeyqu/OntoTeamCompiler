#include "IVisitor.h"
#include "CLastExpressionList.h"

CLastExpressionList::CLastExpressionList( IExpression* expression ) {
	this->expression = expression;
}

void CLastExpressionList::Accept( IVisitor* v ) {
	v->Visit(this);
}