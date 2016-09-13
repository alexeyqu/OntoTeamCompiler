#include "IVisitor.h"
#include "CAssignStatement.h"

CAssignStatement::CAssignStatement( std::string id, IExpression* expression ) {
	this->id = id;
	this->expression = expression;
}

void CAssignStatement::Accept( IVisitor* v ) {
	v->Visit(this);
}