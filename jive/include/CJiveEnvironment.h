#pragma once

#include "ST/CSymbolTable.h"
#include "CProgram.h"

class CJiveEnvironment
{
public:
    CJiveEnvironment() { symbolTable = new CSymbolTable(); }

    void LoadProgram( CProgram *_program ) { program = _program; }

    CProgram *program;
    CSymbolTable *symbolTable;
};