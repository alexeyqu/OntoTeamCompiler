 #pragma once

#include <cstdlib>
#include "IExpression.h"

namespace AST 
{

class CArrayLengthExpression : public IExpression
{
public:
	CArrayLengthExpression( IExpression *_exp );

	void Accept( IVisitor *visitor ) override;

	IExpression *exp;
};

}