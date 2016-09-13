#pragma once

#include "IExpression.h"

class CBinaryExpression : public IExpression 
{
	enum TOperationType {
         		OT_Plus,
         		OT_Minus,
   	};

public:
   	IExpression* leftOperand;
   	IExpression* rightOperand;
   	TOperationType operation;

	CBinaryExpression( IExpression* leftOperand, IExpression* rightOperand );
   virtual void Accept( IVisitor* v ) override;
};