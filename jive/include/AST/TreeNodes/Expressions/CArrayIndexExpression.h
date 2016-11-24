 #pragma once

#include <cstdlib>
#include "../IExpression.h"

class CArrayIndexExpression : public IExpression
{
public:
    CArrayIndexExpression( IExpression *_id, IExpression *_index, IType *_type = new CBuiltInType ( enums::INTEGER ) );

    void Accept( IVisitor *visitor ) override;
    IType *getType() override;

    IExpression *id;
    IExpression *index;
    IType *type;
};
