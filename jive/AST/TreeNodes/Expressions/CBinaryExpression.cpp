#include "CBinaryExpression.h"

CBinaryExpression::CBinaryExpression( IExpression *_leftOperand, enums::TOperation _operation, IExpression *_rightOperand) : \
	leftOperand( _leftOperand ), operation( _operation ), rightOperand( _rightOperand ) {}
 
void CBinaryExpression::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}