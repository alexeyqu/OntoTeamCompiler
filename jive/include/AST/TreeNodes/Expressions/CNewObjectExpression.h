#pragma once

#include "../IExpression.h"

class CNewObjectExpression : public IExpression
{
public:
    CNewObjectExpression( CIdExpression *_objTypeId, CType *_type = new CType ( enums::FAKETYPE ) );

    void Accept( IVisitor *visitor ) override;
    CType *getType() override;

    CIdExpression *objTypeId;
    CType *type;
};