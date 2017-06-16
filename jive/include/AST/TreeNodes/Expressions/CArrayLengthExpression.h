 #pragma once

#include <cstdlib>
#include "IExpression.h"

class CArrayLengthExpression : public IExpression
{
public:
	CArrayLengthExpression( IExpression *_exp );

	void Accept( IVisitor *visitor ) override;

	IExpression *exp;
};
