#pragma once

#include "AST/CProgram.h"

class CJiveEnvironment
{
public:
    CJiveEnvironment() {}

    void LoadProgram( CProgram *_program ) { program = _program; }

    CProgram *program;
};