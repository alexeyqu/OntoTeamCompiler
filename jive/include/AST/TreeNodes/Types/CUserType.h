#pragma once

#include "../IType.h"
#include <string>

class CUserType : public IType
{
public:
	CUserType( std::string name );

	void Accept( IVisitor *visitor ) override;

	std::string name;

	std::string ToString() override;
}; 
