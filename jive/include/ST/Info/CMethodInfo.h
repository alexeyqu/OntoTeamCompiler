#pragma once

#include "СVariableInfo.h"
#include <string>
#include <map>

class CMethodInfo {

public:

	IType returnType;
	std::map< std::string, CVariableInfo> variables;
	std::map< std::string, CVariableInfo> arguments;
};

