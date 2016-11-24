 #pragma once

#include <cstdlib>
#include "../IExpression.h"

class CArrayLengthExpression : public IExpression
{
public:
    CArrayLengthExpression( IExpression *_exp, CType *_type = new CType ( enums::INTEGER ) );

    void Accept( IVisitor *visitor ) override;
    CType *getType() override;

    IExpression *exp;
    CType *type;
};
