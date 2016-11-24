#include "CBinaryBooleanExpression.h"

CBinaryBooleanExpression::CBinaryBooleanExpression( IExpression *_leftOperand, enums::TBooleanOperation _operation, IExpression *_rightOperand, IType *_type ) : \
	leftOperand( _leftOperand ), operation( _operation ), rightOperand( _rightOperand ), type( _type ) {}
 
void CBinaryBooleanExpression::Accept( IVisitor *visitor ) {
	visitor->Visit(this);
}

IType *CBinaryBooleanExpression::getType() {
    // return new CType( enums::BOOLEAN );
    return type;
}