#pragma once

#include "CProgram.h"
#include "CSymbolTable.h"

namespace jive 
{

using AST::CProgram;
using ST::CSymbolTable;

class CJiveEnvironment
{
public:
	CJiveEnvironment();

	void LoadProgram( CProgram *_program ) { program = _program; }

	CProgram *program;
	CSymbolTable *symbolTable;
};

}