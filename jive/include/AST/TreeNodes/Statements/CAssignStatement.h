#pragma once

#include "IStatement.h"
#include "IExpression.h"

namespace AST 
{

class CAssignStatement : public IStatement
{
public:
	CAssignStatement( IExpression *_leftOperand, IExpression *_rightOperand ) : \
		leftOperand( _leftOperand ), rightOperand( _rightOperand ) {}

	void Accept( IVisitor *visitor ) override { visitor->Visit(this); }

	IExpression *getLValue() const { return leftOperand; }
	IExpression *getRValue() const { return rightOperand; }

private:
	IExpression *leftOperand;
	IExpression *rightOperand;
};

}