#pragma once

#include "../IExpression.h"

class CBinaryBooleanExpression : public IExpression
{
public:
	CBinaryBooleanExpression( IExpression *_leftOperand, enums::TBooleanOperation _operation, IExpression *_rightOperand, CType *_type = new CType ( enums::BOOLEAN ) );

	void Accept( IVisitor *visitor ) override;
    CType *getType() override;

	IExpression *leftOperand;
	IExpression *rightOperand;
	enums::TBooleanOperation operation;
    CType *type;
};