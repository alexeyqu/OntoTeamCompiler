#pragma once

#include "../IExpression.h"

class CCompoundExpression : public IExpression
{
public:
	CCompoundExpression( IExpression *_leftExpression, IExpression *_rightExpression, IType *_type = new CBuiltInType ( enums::FAKETYPE ) );

	void Accept( IVisitor *visitor ) override;
	IType *getType() override;

	IExpression *leftExpression;
	IExpression *rightExpression;
	IType *type;
};
