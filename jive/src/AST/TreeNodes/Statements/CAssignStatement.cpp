#include "CAssignStatement.h"

namespace AST 
{

CAssignStatement::CAssignStatement( IExpression *_leftOperand, IExpression *_rightOperand) : \
	leftOperand( _leftOperand ), rightOperand( _rightOperand ) {}
 
void CAssignStatement::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}

}