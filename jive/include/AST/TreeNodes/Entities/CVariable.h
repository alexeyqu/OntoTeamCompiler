#pragma once

#include "CType.h"
#include "IEntity.h"
#include "CIdExpression.h"

namespace AST 
{

class CVariable : public IEntity
{
public:
   	CVariable( CType *_type, CIdExpression *_id ) : \
		type( _type ), id( _id ) {}

   	void Accept( IVisitor *visitor ) override { visitor->Visit( this ); } 

	CSymbol *getSymbol() const { return id->getSymbol(); }
	boost::flyweight<std::string> &getString() const { return id->getString(); }
	CType *getType() const { return type; }
	CIdExpression *getId() const { return id; }

private:
	CType *type;
	CIdExpression *id;
};

}