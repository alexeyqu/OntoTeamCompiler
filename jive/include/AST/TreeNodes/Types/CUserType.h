#pragma once

#include <string>
#include "IType.h"
#include "CSymbol.h"

namespace AST 
{

class CUserType : public IType
{
public:
   	CUserType( CSymbol *name );

   	void Accept( IVisitor *visitor ) override;

	CSymbol *name;

	CSymbol getSymbol();
};
 
}