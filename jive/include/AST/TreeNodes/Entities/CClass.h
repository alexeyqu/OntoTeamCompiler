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
   	CClass( CIdExpression *_id, 
   		CIdExpression *_parentId,
   		CCompoundVariable *_fields,
		CCompoundMethod *_methods ) : \
		id( _id ), parentId( _parentId ), 
		fields( _fields ), methods( _methods ) {}

   	void Accept( IVisitor *visitor ) override { visitor->Visit( this ); }

	CSymbol *getSymbol() const { return id->getSymbol(); }
	boost::flyweight<std::string> &getString() const { return id->getString(); }

	CSymbol *getParentSymbol() const { return parentId->getSymbol(); }
	boost::flyweight<std::string> &getParentString() const { return parentId->getString(); }

	CCompoundVariable *getFields() const { return fields; }
	CCompoundMethod *getMethods() const { return methods; }

	CIdExpression *getId() const { return id; }
	CIdExpression *getParentId() const { return parentId; }

private:
	CIdExpression *id;
   	CIdExpression *parentId;
   	CCompoundVariable *fields;
	CCompoundMethod *methods;
};

inline bool operator==(const CClass& lhs, const CClass& rhs) {
	return ( lhs.getString() == rhs.getString() );
}

}