#pragma once

#include "IStatement.h"
#include "IExpression.h"

namespace AST 
{

class CIfStatement : public IStatement
{
public:
	CIfStatement( IExpression *_expression, IStatement *_thenStatement, IStatement *_elseStatement );

	void Accept( IVisitor *visitor ) override;

	IExpression *expression;
	IStatement *thenStatement;
	IStatement *elseStatement;
};

}