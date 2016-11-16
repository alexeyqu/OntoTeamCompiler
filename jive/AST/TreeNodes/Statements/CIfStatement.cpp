#include "CIfStatement.h"

CIfStatement::CIfStatement( IExpression *_expression, IStatement *_thenStatement, IStatement *_elseStatement ) : \
	expression( _expression ), thenStatement( _thenStatement ), elseStatement( _elseStatement ) {}
 
void CIfStatement::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}