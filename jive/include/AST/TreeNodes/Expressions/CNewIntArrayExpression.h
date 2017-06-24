#pragma once

#include "IExpression.h"

namespace AST 
{

class CNewIntArrayExpression : public IExpression
{
public:
	CNewIntArrayExpression( IExpression *_arrSize );

	void Accept( IVisitor *visitor ) override;

	IExpression *arrSize;
};

}