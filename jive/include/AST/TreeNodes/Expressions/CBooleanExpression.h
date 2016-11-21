#pragma once

#include <cstdlib>
#include "../IExpression.h"

class CBooleanExpression : public IExpression
{
public:
   	CBooleanExpression( bool _value );

   	void Accept( IVisitor *visitor ) override;
   	enums::TType getType() override;

   	bool value;
	enums::TType type;
};