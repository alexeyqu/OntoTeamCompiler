#pragma once

#include "IExpression.h"

namespace AST 
{

using jive::TArithmeticOperation;

class CBinaryExpression : public IExpression
{
public:
	CBinaryExpression( IExpression *_leftOperand, TArithmeticOperation _operation, IExpression *_rightOperand ) : \
		leftOperand( _leftOperand ), operation( _operation ), rightOperand( _rightOperand ) {}
 
	void Accept( IVisitor *visitor ) override { visitor->Visit( this ); }

	IExpression *getLeftOperand() const { return leftOperand; }
	IExpression *getRightOperand() const { return rightOperand; }
	TArithmeticOperation getOperator() const { return operation; }

private:
	IExpression *leftOperand;
	IExpression *rightOperand;
	TArithmeticOperation operation;
};

}