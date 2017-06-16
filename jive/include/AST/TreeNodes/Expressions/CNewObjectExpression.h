#pragma once

#include "IExpression.h"

class CNewObjectExpression : public IExpression
{
public:
    CNewObjectExpression( CIdExpression *_objTypeId );

    void Accept( IVisitor *visitor ) override;

    CIdExpression *objTypeId;
};