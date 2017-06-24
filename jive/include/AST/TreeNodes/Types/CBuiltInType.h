
#pragma once

#include "IType.h"
#include "CSymbol.h"

namespace AST 
{

class CBuiltInType : public IType
{
public:
   	CBuiltInType( jive::TType _type );

   	void Accept( IVisitor *visitor ) override;

	CSymbol *name;

	CSymbol getSymbol(); // TODO make static symbols
};

}