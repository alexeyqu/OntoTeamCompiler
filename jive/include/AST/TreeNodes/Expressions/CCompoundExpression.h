#pragma once

#include "../IExpression.h"

class CCompoundExpression : public IExpression
{
public:
	CCompoundExpression( IExpression *_leftExpression, IExpression *_rightExpression );

	void Accept( IVisitor *visitor ) override;

	IExpression *leftExpression;
	IExpression *rightExpression;
};
