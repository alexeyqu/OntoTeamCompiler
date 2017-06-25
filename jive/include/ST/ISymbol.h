#pragma once

#include "CSymbol.h"
#include "Coordinates.h"

namespace ST
{

using jive::Coordinates;

class CTypeSymbol;

class ISymbol
{
public:
    ISymbol( CSymbol *_name, CTypeSymbol *_type ) : name( _name ), type( _type ) {}

    CTypeSymbol *type;
	CSymbol *name;
    Coordinates coordinates;
};

}