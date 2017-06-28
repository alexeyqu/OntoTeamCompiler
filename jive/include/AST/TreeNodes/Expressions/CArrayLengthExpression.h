 #pragma once

#include <cstdlib>
#include "IExpression.h"

namespace AST 
{

class CArrayLengthExpression : public IExpression
{
public:
	CArrayLengthExpression( IExpression *_exp ) : exp( _exp ) {}

	void Accept( IVisitor *visitor ) override { visitor->Visit( this ); }

	IExpression *getValue() const { return exp; }

private:
	IExpression *exp;
};

}