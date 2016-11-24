#include "CBinaryExpression.h"

CBinaryExpression::CBinaryExpression( IExpression *_leftOperand, enums::TArithmeticOperation _operation, IExpression *_rightOperand, CType *_type ) : \
	leftOperand( _leftOperand ), operation( _operation ), rightOperand( _rightOperand ), type( _type ) {}
 
void CBinaryExpression::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}

CType *CBinaryExpression::getType() {
    // return new CType( enums::INTEGER );
    return type;
}