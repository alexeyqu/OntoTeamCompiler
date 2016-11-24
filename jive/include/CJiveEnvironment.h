#pragma once

#include "CProgram.h"

class CJiveEnvironment
{
public:
    CJiveEnvironment( CProgram *_program ) : program( _program ) {}

    CProgram *program;
};