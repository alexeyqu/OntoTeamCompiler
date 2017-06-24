#pragma once

#include <cstdlib>
#include "IExpression.h"

namespace AST 
{

class CBooleanExpression : public IExpression
{
public:
   	CBooleanExpression( bool _value );

   	void Accept( IVisitor *visitor ) override;

   	bool value;
};

}