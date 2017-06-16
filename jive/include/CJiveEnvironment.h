#pragma once

#include "CProgram.h"

class CJiveEnvironment
{
public:
	CJiveEnvironment() {}

	void LoadProgram( CProgram *_program ) { program = _program; }

	CProgram *program;
};