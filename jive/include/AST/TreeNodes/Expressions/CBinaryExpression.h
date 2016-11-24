#pragma once

#include "../IExpression.h"

class CBinaryExpression : public IExpression
{
public:
	CBinaryExpression( IExpression *_leftOperand, enums::TArithmeticOperation _operation, IExpression *_rightOperand, CType *_type = new CType ( enums::INTEGER ) );

	void Accept( IVisitor *visitor ) override;
    CType *getType() override;

	IExpression *leftOperand;
	IExpression *rightOperand;
	enums::TArithmeticOperation operation;
    CType *type;
};