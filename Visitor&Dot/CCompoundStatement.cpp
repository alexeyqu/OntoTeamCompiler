#include "IVisitor.h"
#include "CCompoundStatement.h"

CCompoundStatement::CCompoundStatement( IStatement* leftStatement, IStatement* rightStatement ) {
	this->leftStatement = leftStatement;
	this->rightStatement = rightStatement;
}

void CCompoundStatement::Accept( IVisitor* v ) {
	v->Visit(this);
}