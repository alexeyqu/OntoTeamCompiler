#pragma once

#include "IExpression.h"

class CLastExpressionList : public IExpression
{
public:

	IExpression* expression;

	CLastExpressionList( IExpression* expression );
	virtual void Accept( IVisitor* v ) override;
};