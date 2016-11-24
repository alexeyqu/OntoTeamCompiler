#pragma once

#include "../IExpression.h"

class CNewIntArrayExpression : public IExpression
{
public:
    CNewIntArrayExpression( IExpression *_arrSize, IType *_type = new CBuiltInType ( enums::INTEGERARRAY ) );

    void Accept( IVisitor *visitor ) override;
    IType *getType() override;

    IExpression *arrSize;
    IType *type;
};