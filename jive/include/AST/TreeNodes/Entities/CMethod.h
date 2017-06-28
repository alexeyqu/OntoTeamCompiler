#pragma once

#include "CType.h"
#include "IEntity.h"
#include "IExpression.h"
#include "CIdExpression.h"

namespace AST 
{

class CMethod : public IEntity
{
public:
   	CMethod( CType *_returnType, CIdExpression *_id, 
   		CCompoundArgument *_arguments,
   		CCompoundVariable *_variables,
		CCompoundStatement *_statements,
		IExpression *_returnExpression ) : \
	returnType( _returnType ), id( _id ), arguments( _arguments ),
	variables( _variables ),
	statements( _statements ),
	returnExpression( _returnExpression ) {}

   	void Accept( IVisitor *visitor ) override { visitor->Visit( this ); }

	CSymbol *getSymbol() const { return id->getSymbol(); }
	boost::flyweight<std::string> &getString() const { return id->getString(); }

	CCompoundArgument *getArguments() const { return arguments; }
	CCompoundVariable *getVariables() const { return variables; }
	CCompoundStatement *getStatements() const { return statements; }

	CType *getReturnType() const { return returnType; }
	IExpression *getReturnExpression() const { return returnExpression; }
	CIdExpression *getId() const { return id; }

private:
	CType *returnType;
	CIdExpression *id;
	CCompoundArgument *arguments;
	CCompoundVariable *variables;
	CCompoundStatement *statements;
	IExpression *returnExpression;
};

}