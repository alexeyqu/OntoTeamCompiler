#include "IVisitor.h"
#include "CProgram.h"

CProgram::CProgram( IExpression* expr ) {
	this->expr = expr;
}
 
void CProgram::Accept( IVisitor* v ) {
	v->Visit(this);
}