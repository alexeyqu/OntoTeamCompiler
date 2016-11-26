#pragma once

#include "../IVisitorTarget.h"
#include <string>

class IType : public IVisitorTarget 
{
protected:
	IType( enums::TType _type ) : type( _type ) {}
public:
	enums::TType type;

	virtual std::string ToString() = 0;	
};
