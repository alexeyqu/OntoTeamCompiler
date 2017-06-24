#pragma once

#include "IExpression.h"

namespace AST 
{

class CBinaryExpression : public IExpression
{
public:
	CBinaryExpression( IExpression *_leftOperand, jive::TArithmeticOperation _operation, IExpression *_rightOperand );

	void Accept( IVisitor *visitor ) override;

	IExpression *leftOperand;
	IExpression *rightOperand;
	jive::TArithmeticOperation operation;
};

}