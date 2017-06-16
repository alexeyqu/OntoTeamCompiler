#pragma once

#include "IExpression.h"

class CMethodCallExpression : public IExpression
{
public:
	CMethodCallExpression( IExpression *_base, CIdExpression *_methodId, IExpression *_arg );

	void Accept( IVisitor *visitor ) override;

	IExpression *base;
	CIdExpression *methodId;
	IExpression *arg;
};