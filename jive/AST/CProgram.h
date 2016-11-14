#pragma once

#include "IVisitorTarget.h"
#include "TreeNodes/IExpression.h"
#include "TreeNodes/CBinaryExpression.h"

class CProgram : public IVisitorTarget 
{
public:
	IExpression *expr;

	CProgram( IExpression* expr );
	virtual void Accept( IVisitor* v ) override;
};