#pragma once

#include "../IExpression.h"

class CBinaryBooleanExpression : public IExpression
{
public:
	CBinaryBooleanExpression( IExpression *_leftOperand, enums::TBooleanOperation _operation, IExpression *_rightOperand );

	void Accept( IVisitor *visitor ) override;

	IExpression *leftOperand;
	IExpression *rightOperand;
	enums::TBooleanOperation operation;
};