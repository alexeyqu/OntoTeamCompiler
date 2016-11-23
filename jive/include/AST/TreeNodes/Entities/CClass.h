 #pragma once

#include "../IEntity.h"
#include "../IStatement.h"
#include "../IExpression.h"

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