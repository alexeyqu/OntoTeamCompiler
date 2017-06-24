 #pragma once

#include "IEntity.h"
#include "IExpression.h"
#include "IStatement.h"

namespace AST 
{

class CClass : public IEntity
{
public:
   	CClass( CIdExpression *_name, 
   		CIdExpression *_parentName,
   		CCompoundVariable *_fields,
		CCompoundMethod *_methods );

   	void Accept( IVisitor *visitor ) override;

	CIdExpression *name;
   	CIdExpression *parentName;
   	CCompoundVariable *fields;
	CCompoundMethod *methods;
};

}