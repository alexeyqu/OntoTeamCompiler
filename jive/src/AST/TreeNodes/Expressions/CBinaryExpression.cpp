#include "CBinaryExpression.h"

CBinaryExpression::CBinaryExpression( IExpression *_leftOperand, enums::TArithmeticOperation _operation, IExpression *_rightOperand) : \
	leftOperand( _leftOperand ), operation( _operation ), rightOperand( _rightOperand ), type( enums::INTEGER ) {}
 
void CBinaryExpression::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}

enums::TType CBinaryExpression::getType() {
	return type;
}