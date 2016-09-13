#pragma once

#include "IExpression.h"

class CBinaryExpression : public IExpression 
{
   	IExpression* leftOperand;
   	IExpression* rightOperand;
 
   	enum TOperationType {
         		OT_Plus,
         		OT_Minus,
   	};
   	TOperationType operation;

public:

	CBinaryExpression( IExpression* leftOperand, IExpression* rightOperand );
   virtual void Accept( IVisitor* v ) override;
};