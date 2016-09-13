#include "IVisitor.h"
#include "CPrintStatement.h"

CPrintStatement::CPrintStatement( IStatement* statement ) {
	this->statement = statement;
}

void CPrintStatement::Accept( IVisitor* v ) {
	v->Visit(this);
}