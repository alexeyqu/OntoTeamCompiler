#pragma once

#include "CProgram.h"
#include "CSymbolTable.h"
#include "CTypeSymbol.h"
#include "CTypeMap.h"
#include "CClassMap.h"
#include "CSymbol.h"
#include "Types.h"

namespace jive 
{

using AST::CProgram;
using AST::CType;
using ST::CSymbol;
using ST::CSymbolTable;
using ST::CTypeSymbol;
using ST::CTypeMap;
using ST::CClassMap;

class CJiveEnvironment
{
public:
	CJiveEnvironment();

	void LoadProgram( CProgram *_program ) { program = _program; }

	CProgram *program;
	CSymbolTable *symbolTable;
	CTypeMap *typeMap;
	CClassMap *classMap;
};

}