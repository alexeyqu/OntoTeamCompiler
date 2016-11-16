#pragma once

#include "IStatement.h"
#include "IExpression.h"

class CPrintStatement : public IStatement
{
public:
	CPrintStatement( IExpression *_operand );

	void Accept( IVisitor *visitor ) override;

	IExpression *operand;
};