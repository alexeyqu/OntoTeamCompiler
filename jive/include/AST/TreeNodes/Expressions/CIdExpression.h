#pragma once

#include <string>
#include "../IExpression.h"
#include "../../../TypeChecker/CSymbolTable.h"

class CSymbolTable;
extern CSymbolTable symbolTable;

class CIdExpression : public IExpression
{
public:
   	CIdExpression( const char *_name );

   	void Accept( IVisitor *visitor ) override;
   	enums::TType getType() override;

   	std::string name;
	enums::TType type;
};