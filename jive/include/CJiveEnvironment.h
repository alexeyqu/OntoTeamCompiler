#pragma once

#include "ST/CSymbolTable.h"
#include "CProgram.h"

class CJiveEnvironment
{
public:
    CJiveEnvironment() {}

    void LoadProgram( CProgram *_program ) { program = _program; }

    CProgram *program;
    CSymbolTable *symbolTable;
};