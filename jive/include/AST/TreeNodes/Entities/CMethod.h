#pragma once

#include "../IEntity.h"
#include "../IStatement.h"
#include "../IExpression.h"

class CMethod : public IEntity
{
public:
   	CMethod( CType *_returnType, CIdExpression *_id, 
   		CCompoundArgument *_arguments,
   		CCompoundVariable *_variables,
		CCompoundStatement *_statements,
		IExpression *_returnExpression );

   	void Accept( IVisitor *visitor ) override;

	CType *returnType;
	CIdExpression *id;
	CCompoundArgument *arguments;
	CCompoundVariable *variables;
	CCompoundStatement *statements;
	IExpression *returnExpression;
};