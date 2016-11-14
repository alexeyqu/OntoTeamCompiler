#pragma once

#include "IExpression.h"

class CBinaryExpression : public IExpression
{
public:
	enum TOperationType {
		OT_Plus,
		OT_Minus,
	};

	IExpression* leftOperand;
	IExpression* rightOperand;
	TOperationType operation;

	CBinaryExpression( IExpression* leftOperand, TOperationType operation, IExpression* rightOperand );
	virtual void Accept( IVisitor* v ) override;
};