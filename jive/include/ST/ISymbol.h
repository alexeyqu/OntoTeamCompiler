#pragma once

#include "IType.h"
#include <string>
#include "Coordinates.h"

 class ISymbol {
public:
	ISymbol( std::string _name, IType* _type ) : name( _name ), type( _type ) {}
	std::string name;
	IType* type;
	Coordinates coordinates;
};