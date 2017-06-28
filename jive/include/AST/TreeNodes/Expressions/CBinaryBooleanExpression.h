#pragma once

#include "IExpression.h"

namespace AST 
{

using jive::TBooleanOperation;

class CBinaryBooleanExpression : public IExpression
{
public:
	CBinaryBooleanExpression( IExpression *_leftOperand, TBooleanOperation _operation, IExpression *_rightOperand ) : \
		leftOperand( _leftOperand ), operation( _operation ), rightOperand( _rightOperand ) {}

	void Accept( IVisitor *visitor ) override { visitor->Visit(this); }

	IExpression *getLeftOperand() const { return leftOperand; }
	IExpression *getRightOperand() const { return rightOperand; }
	TBooleanOperation getOperator() const { return operation; }

private:
	IExpression *leftOperand;
	IExpression *rightOperand;
	TBooleanOperation operation;
};

}