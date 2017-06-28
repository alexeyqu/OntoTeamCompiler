#pragma once

#include "IExpression.h"

namespace AST 
{

class CNewObjectExpression : public IExpression
{
public:
    CNewObjectExpression( CIdExpression *_objTypeId ) : objTypeId( _objTypeId ) {}

    void Accept( IVisitor *visitor ) override { visitor->Visit( this ); }

	CSymbol *getSymbol() const { return objTypeId->getSymbol(); }
	boost::flyweight<std::string> &getString() const { return objTypeId->getString(); }

	CIdExpression *getClassId() const { return objTypeId; }

private:
    CIdExpression *objTypeId;
};

}