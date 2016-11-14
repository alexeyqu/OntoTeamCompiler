#pragma once

#include "IExpression.h"

class CNumberExpression : public IExpression
{
public:
   	int number;

   	CNumberExpression( const char* number );
   	virtual void Accept( IVisitor* v ) override;
};