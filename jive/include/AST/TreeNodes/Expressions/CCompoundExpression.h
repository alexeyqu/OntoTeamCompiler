#pragma once

#include "IExpression.h"

namespace AST 
{

class CCompoundExpression : public IExpression
{
public:
	CCompoundExpression( IExpression *_leftExpression, IExpression *_rightExpression ) : \
		leftExpression( _leftExpression ), rightExpression( _rightExpression ) {}

	void Accept( IVisitor *visitor ) override { visitor->Visit(this); }

	IExpression *getLeftExpression() const { return leftExpression; }
	IExpression *getRightExpression() const { return rightExpression; }

private:
	IExpression *leftExpression;
	IExpression *rightExpression;
};

}