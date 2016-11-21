#include "CBinaryBooleanExpression.h"

CBinaryBooleanExpression::CBinaryBooleanExpression( IExpression *_leftOperand, enums::TBooleanOperation _operation, IExpression *_rightOperand) : \
	leftOperand( _leftOperand ), operation( _operation ), rightOperand( _rightOperand ), type( enums::BOOLEAN ) {}
 
void CBinaryBooleanExpression::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}

enums::TType CBinaryBooleanExpression::getType() {
	return type;
}