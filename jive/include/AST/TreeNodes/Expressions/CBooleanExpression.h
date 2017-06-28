#pragma once

#include <cstdlib>
#include "IExpression.h"

namespace AST 
{

class CBooleanExpression : public IExpression
{
public:
   	CBooleanExpression( bool _value ) : value( _value ) {}

   	void Accept( IVisitor *visitor ) override { visitor->Visit( this ); }

	bool getValue() const { return value; }

private:
   	bool value;
};

}