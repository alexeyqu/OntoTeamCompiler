#pragma once

#include "../IExpression.h"

class CMethodCallExpression : public IExpression
{
public:
    CMethodCallExpression( IExpression *_base, CIdExpression *_methodId, IExpression *_arg, IType *_type = new CBuiltInType ( enums::FAKETYPE ) );

    void Accept( IVisitor *visitor ) override;
    IType *getType() override;

    IExpression *base;
    CIdExpression *methodId;
    IExpression *arg;
    IType *type;
};