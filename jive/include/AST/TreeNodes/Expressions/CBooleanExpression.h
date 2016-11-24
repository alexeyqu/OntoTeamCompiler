#pragma once

#include <cstdlib>
#include "../IExpression.h"

class CBooleanExpression : public IExpression
{
public:
   	CBooleanExpression( bool _value, CType *_type = new CType ( enums::BOOLEAN ) );

   	void Accept( IVisitor *visitor ) override;
    CType *getType() override;

   	bool value;
    CType *type;
};