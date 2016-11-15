#include "../IVisitor.h"
#include "CBinaryExpression.h"

CBinaryExpression::CBinaryExpression( IExpression *_leftOperand, enums::TOperation _operation, IExpression *_rightOperand) : \
	leftOperand( _leftOperand ), rightOperand( _rightOperand ), operation( _operation ) {}
 
void CBinaryExpression::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}