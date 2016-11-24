 #pragma once

#include <cstdlib>
#include "../IExpression.h"

class CArrayLengthExpression : public IExpression
{
public:
    CArrayLengthExpression( IExpression *_exp, IType *_type = new CBuiltInType ( enums::INTEGER ) );

    void Accept( IVisitor *visitor ) override;
    IType *getType() override;

    IExpression *exp;
    IType *type;
};
