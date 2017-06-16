 #pragma once

#include <cstdlib>
#include "IExpression.h"

class CArrayIndexExpression : public IExpression
{
public:
	CArrayIndexExpression( IExpression *_id, IExpression *_index );

	void Accept( IVisitor *visitor ) override;

	IExpression *id;
	IExpression *index;
};
