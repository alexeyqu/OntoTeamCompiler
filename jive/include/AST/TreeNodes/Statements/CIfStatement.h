#pragma once

#include "IStatement.h"
#include "IExpression.h"

namespace AST 
{

class CIfStatement : public IStatement
{
public:
	CIfStatement( IExpression *_expression, IStatement *_thenStatement, IStatement *_elseStatement ) : \
		expression( _expression ), thenStatement( _thenStatement ), elseStatement( _elseStatement ) {}

	void Accept( IVisitor *visitor ) override { visitor->Visit(this); }

	IExpression *getExpression() const { return expression; }
	IStatement *getThenStatement() const { return thenStatement; }
	IStatement *getElseStatement() const { return elseStatement; }

private:
	IExpression *expression;
	IStatement *thenStatement;
	IStatement *elseStatement;
};

}