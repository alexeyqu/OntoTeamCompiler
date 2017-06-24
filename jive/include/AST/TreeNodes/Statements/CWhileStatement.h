#pragma once

#include "IStatement.h"
#include "IExpression.h"

namespace AST 
{

class CWhileStatement : public IStatement
{
public:
	CWhileStatement( IExpression *_expression, IStatement *_loopStatement );

	void Accept( IVisitor *visitor ) override;

	IExpression *expression;
	IStatement *loopStatement;
};

}