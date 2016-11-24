#pragma once

#include "../IExpression.h"

class CNewObjectExpression : public IExpression
{
public:
    CNewObjectExpression( CIdExpression *_objTypeId, IType *_type = new CBuiltInType ( enums::FAKETYPE ) );

    void Accept( IVisitor *visitor ) override;
    IType *getType() override;

    CIdExpression *objTypeId;
    IType *type;
};