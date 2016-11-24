#pragma once

#include <cstdlib>
#include "../IExpression.h"

class CBooleanExpression : public IExpression
{
public:
   	CBooleanExpression( bool _value, IType *_type = new CBuiltInType ( enums::BOOLEAN ) );

   	void Accept( IVisitor *visitor ) override;
    IType *getType() override;

   	bool value;
    IType *type;
};