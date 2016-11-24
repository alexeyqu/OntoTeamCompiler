 #pragma once

#include "../IVisitorTarget.h"

class IType : public IVisitorTarget 
{
protected:
	IType( enums::TType _type ) : type( _type ) {}
public:
	enums::TType type;
};
