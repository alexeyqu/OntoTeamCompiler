#include "IVisitor.h"
#include "CPrintStatement.h"
#include "IExpression.h"

CPrintStatement::CPrintStatement( IExpression* expression ) {
	this->expression = expression;
}

void CPrintStatement::Accept( IVisitor* v ) {
	v->Visit(this);
}