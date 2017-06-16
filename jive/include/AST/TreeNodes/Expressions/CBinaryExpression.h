#pragma once

#include "IExpression.h"

class CBinaryExpression : public IExpression
{
public:
	CBinaryExpression( IExpression *_leftOperand, enums::TArithmeticOperation _operation, IExpression *_rightOperand );

	void Accept( IVisitor *visitor ) override;

	IExpression *leftOperand;
	IExpression *rightOperand;
	enums::TArithmeticOperation operation;
};