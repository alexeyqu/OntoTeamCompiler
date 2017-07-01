#pragma once

#include <string>
#include <boost/flyweight.hpp>
#include "IExpression.h"
#include "CSymbol.h"

namespace AST 
{

class CIdExpression : public IExpression
{
public:
   	CIdExpression( CSymbol *_symbol ) : symbol( _symbol ) {}

   	void Accept( IVisitor *visitor ) override { visitor->Visit( this ); }

	CSymbol *getSymbol() const { return symbol; }
	boost::flyweight<std::string>getString() const { return symbol->getString(); } 

private:
   	CSymbol *symbol;
};

}