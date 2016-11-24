#pragma once

#include "../IExpression.h"

class CNewIntArrayExpression : public IExpression
{
public:
    CNewIntArrayExpression( IExpression *_arrSize, CType *_type = new CType ( enums::INTEGERARRAY ) );

    void Accept( IVisitor *visitor ) override;
    CType *getType() override;

    IExpression *arrSize;
    CType *type;
};