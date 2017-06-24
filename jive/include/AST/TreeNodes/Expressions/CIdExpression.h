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
   	CIdExpression( CSymbol *_name );

   	void Accept( IVisitor *visitor ) override;

	boost::flyweight<std::string> getName() const;

   	CSymbol *name;
};

}