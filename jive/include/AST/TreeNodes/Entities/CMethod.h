#pragma once

#include "../IType.h"
#include "../IEntity.h"
#include "../IExpression.h"

class CMethod : public IEntity
{
public:
   	CMethod( IType *_returnType, CIdExpression *_id, 
   		CCompoundArgument *_arguments,
   		CCompoundVariable *_variables,
		CCompoundStatement *_statements,
		IExpression *_returnExpression );

   	void Accept( IVisitor *visitor ) override;

	IType *returnType;
	CIdExpression *id;
	CCompoundArgument *arguments;
	CCompoundVariable *variables;
	CCompoundStatement *statements;
	IExpression *returnExpression;
};