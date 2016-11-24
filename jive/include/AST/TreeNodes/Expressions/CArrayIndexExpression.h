 #pragma once

#include <cstdlib>
#include "../IExpression.h"

class CArrayIndexExpression : public IExpression
{
public:
    CArrayIndexExpression( IExpression *_id, IExpression *_index, CType *_type = new CType ( enums::INTEGER ) );

    void Accept( IVisitor *visitor ) override;
    CType *getType() override;

    IExpression *id;
    IExpression *index;
    CType *type;
};
