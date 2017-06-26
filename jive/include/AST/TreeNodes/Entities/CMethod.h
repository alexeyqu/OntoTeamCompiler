#pragma once

#include "CType.h"
#include "IEntity.h"
#include "IExpression.h"

namespace AST 
{

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

}