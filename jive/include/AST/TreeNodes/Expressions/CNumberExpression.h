#pragma once

#include <cstdlib>
#include "../IExpression.h"

class CNumberExpression : public IExpression
{
public:
   	CNumberExpression( const char *_number, CType *_type = new CType ( enums::INTEGER ) );

   	void Accept( IVisitor *visitor ) override;
    CType *getType() override;

   	int number;
    CType *type;
};