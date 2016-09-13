#pragma once

#include "IExpression.h"

class CNumberExpression : public IExpression 
{
public:

   	int value;

   	CNumberExpression( int value ); 
   	virtual void Accept( IVisitor* v ) override;
};
