#pragma once

#include "../IExpression.h"

class CMethodCallExpression : public IExpression
{
public:
    CMethodCallExpression( IExpression *_base, CIdExpression *_methodId, IExpression *_arg, CType *_type = new CType ( enums::FAKETYPE ) );

    void Accept( IVisitor *visitor ) override;
    CType *getType() override;

    IExpression *base;
    CIdExpression *methodId;
    IExpression *arg;
    CType *type;
};