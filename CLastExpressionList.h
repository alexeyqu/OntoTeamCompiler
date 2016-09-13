#pragma once

#include "IExpression.h"

class CLastExpressionList : public IExpression
{
	IExpression* expression;

public:
	CLastExpressionList( IExpression* expression );
	virtual void Accept( IVisitor* v ) override;
};