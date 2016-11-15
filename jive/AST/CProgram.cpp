#include "IVisitor.h"
#include "CProgram.h"

CProgram::CProgram( IExpression *_expression ) : expression( _expression ) {}
 
void CProgram::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}