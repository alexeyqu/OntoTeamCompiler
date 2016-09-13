#pragma once

#include "IExpression.h"

class CNumberExpression : public IExpression 
{
   	int value;

public:

   	CNumberExpression( int value ); 
   	virtual void Accept( IVisitor* v ) override;
};
