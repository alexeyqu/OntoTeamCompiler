 #pragma once

#include "IEntity.h"
#include "IExpression.h"
#include "IStatement.h"
#include "CIdExpression.h"

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

inline bool operator==(const CClass& lhs, const CClass& rhs) {
	return ( lhs.name->getName() == rhs.name->getName() );
}

}