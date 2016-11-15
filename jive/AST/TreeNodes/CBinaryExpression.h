#pragma once

#include "IExpression.h"

class CBinaryExpression : public IExpression
{
public:
	IExpression* leftOperand;
	IExpression* rightOperand;
	enums::TOperation operation;

	CBinaryExpression( IExpression* leftOperand, enums::TOperation operation, IExpression* rightOperand );
	virtual void Accept( IVisitor* v ) override;
};