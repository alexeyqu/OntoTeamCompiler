#pragma once

#include "CProgram.h"
#include "CSymbolTable.h"

class CJiveEnvironment
{
public:
	CJiveEnvironment() : symbolTable( new CSymbolTable() ){}

	void LoadProgram( CProgram *_program ) { program = _program; }

	CProgram *program;
	CSymbolTable *symbolTable;
};