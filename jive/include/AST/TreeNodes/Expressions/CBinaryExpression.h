#pragma once

#include "../IExpression.h"

class CBinaryExpression : public IExpression
{
public:
	CBinaryExpression( IExpression *_leftOperand, enums::TArithmeticOperation _operation, IExpression *_rightOperand, IType *_type = new CBuiltInType ( enums::INTEGER ) );

	void Accept( IVisitor *visitor ) override;
    IType *getType() override;

	IExpression *leftOperand;
	IExpression *rightOperand;
	enums::TArithmeticOperation operation;
    IType *type;
};