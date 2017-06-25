#pragma once

#include "CProgram.h"
#include "CSymbolTable.h"
#include "CTypeSymbol.h"
#include "CTypeTable.h"
#include "CSymbol.h"

namespace jive 
{

using AST::CProgram;
using ST::CSymbol;
using ST::CSymbolTable;
using ST::CTypeSymbol;
using ST::CTypeTable;

class CJiveEnvironment
{
public:
	CJiveEnvironment();

	void LoadProgram( CProgram *_program ) { program = _program; }

	CProgram *program;
	CSymbolTable *symbolTable;
	CTypeTable *typeTable;
};

}