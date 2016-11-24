#pragma once

#include <cstdlib>
#include "../IExpression.h"

class CNumberExpression : public IExpression
{
public:
   	CNumberExpression( const char *_number, IType *_type = new CBuiltInType ( enums::INTEGER ) );

   	void Accept( IVisitor *visitor ) override;
    IType *getType() override;

   	int number;
    IType *type;
};