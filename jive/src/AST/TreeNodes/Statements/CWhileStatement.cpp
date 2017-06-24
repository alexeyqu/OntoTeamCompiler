#include "CWhileStatement.h"

namespace AST 
{

CWhileStatement::CWhileStatement( IExpression *_expression, IStatement *_loopStatement ) : \
	expression( _expression ), loopStatement( _loopStatement ) {}
 
void CWhileStatement::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}

}