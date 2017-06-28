#pragma once

#include "IStatement.h"
#include "IExpression.h"

namespace AST 
{

class CPrintStatement : public IStatement
{
public:
	CPrintStatement( IExpression *_operand ) : operand( _operand ) {}

	void Accept( IVisitor *visitor ) override { visitor->Visit(this); }

	IExpression *getExpression() const { return operand; }

private:
	IExpression *operand;
};

}