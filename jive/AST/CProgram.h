#pragma once

#include "IVisitorTarget.h"
#include "TreeNodes/IExpression.h"
#include "TreeNodes/CBinaryExpression.h"

class CProgram : public IVisitorTarget 
{
public:
	CProgram( IExpression *_expression );

	void Accept( IVisitor *visitor ) override;

	IExpression *expression;
};