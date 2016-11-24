#pragma once

#include "../IExpression.h"

class CBinaryBooleanExpression : public IExpression
{
public:
	CBinaryBooleanExpression( IExpression *_leftOperand, enums::TBooleanOperation _operation, IExpression *_rightOperand, IType *_type = new CBuiltInType ( enums::BOOLEAN ) );

	void Accept( IVisitor *visitor ) override;
    IType *getType() override;

	IExpression *leftOperand;
	IExpression *rightOperand;
	enums::TBooleanOperation operation;
    IType *type;
};