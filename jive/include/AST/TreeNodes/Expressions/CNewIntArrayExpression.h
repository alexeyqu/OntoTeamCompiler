#pragma once

#include "IExpression.h"

namespace AST 
{

class CNewIntArrayExpression : public IExpression
{
public:
	CNewIntArrayExpression( IExpression *_arrSize ) : arrSize( _arrSize ) {}

	void Accept( IVisitor *visitor ) override { visitor->Visit( this ); }

	IExpression *getArrSize() const { return arrSize; }

private:
	IExpression *arrSize;
};

}