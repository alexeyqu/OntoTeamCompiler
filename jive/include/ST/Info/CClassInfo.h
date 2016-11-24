#pragma once

#include <string>
#include <map>
#include "CMethodInfo.h"
#include "CVariableInfo.h"

class CClassInfo {

public:

	std::string className;
	std::map< std::string, CVariableInfo > fields;
	std::map< std::string, CMethodInfo > methods;
	std::string parentName;
};