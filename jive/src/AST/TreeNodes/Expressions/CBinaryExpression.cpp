#include "CBinaryExpression.h"

namespace AST 
{

CBinaryExpression::CBinaryExpression( IExpression *_leftOperand, jive::TArithmeticOperation _operation, IExpression *_rightOperand) : \
	leftOperand( _leftOperand ), operation( _operation ), rightOperand( _rightOperand ) {}
 
void CBinaryExpression::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}

}