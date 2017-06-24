#pragma once

#include "IExpression.h"

namespace AST 
{

class CBinaryBooleanExpression : public IExpression
{
public:
	CBinaryBooleanExpression( IExpression *_leftOperand, jive::TBooleanOperation _operation, IExpression *_rightOperand );

	void Accept( IVisitor *visitor ) override;

	IExpression *leftOperand;
	IExpression *rightOperand;
	jive::TBooleanOperation operation;
};

}