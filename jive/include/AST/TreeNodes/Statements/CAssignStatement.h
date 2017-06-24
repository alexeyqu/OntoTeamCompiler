#pragma once

#include "IStatement.h"
#include "IExpression.h"

namespace AST 
{

class CAssignStatement : public IStatement
{
public:
	CAssignStatement( IExpression *_leftOperand, IExpression *_rightOperand );

	void Accept( IVisitor *visitor ) override;

	IExpression *leftOperand;
	IExpression *rightOperand;
};

}