#pragma once

#include "IStatement.h"
#include "IExpression.h"

namespace AST 
{

class CWhileStatement : public IStatement
{
public:
	CWhileStatement( IExpression *_expression, IStatement *_loopStatement ) : \
		expression( _expression ), loopStatement( _loopStatement ) {} 

	void Accept( IVisitor *visitor ) override { visitor->Visit(this); }

	IExpression *getExpression() const { return expression; }
	IStatement *getStatement() const { return loopStatement; }

private:
	IExpression *expression;
	IStatement *loopStatement;
};

}