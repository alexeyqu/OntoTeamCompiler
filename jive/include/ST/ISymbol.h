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

	CSymbol *getSymbol() const { return name; }
	boost::flyweight<std::string> &getString() const { return name->getString(); }
	CTypeSymbol *getTypeSymbol() const { return type; }

private:
    CTypeSymbol *type;
	CSymbol *name;
    // Coordinates coordinates;
};

}