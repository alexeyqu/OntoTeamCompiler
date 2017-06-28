#pragma once

#include "CProgram.h"
#include "CSymbolTable.h"
#include "CTypeSymbol.h"
#include "CTypeTable.h"
#include "CClassTable.h"
#include "CSymbol.h"
#include "Types.h"

namespace jive 
{

using AST::CProgram;
using AST::CType;
using ST::CSymbol;
using ST::CSymbolTable;
using ST::CTypeSymbol;
using ST::CTypeTable;
using ST::CClassTable;

class CJiveEnvironment
{
public:
	CJiveEnvironment();

	void LoadProgram( CProgram *_program ) { program = _program; }

	CProgram *program;
	CSymbolTable *symbolTable;
	CTypeTable *typeTable;
	CClassTable *classTable;
};

}