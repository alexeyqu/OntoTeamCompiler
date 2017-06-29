#pragma once

#include "CSymbol.h"
#include "Coordinates.h"
#include "CTypeSymbol.h"

namespace ST
{

using jive::Coordinates;

class ISymbol
{
public:
    ISymbol( CSymbol *_name, CTypeSymbol *_type ) : name( _name ), type( _type ) {}

	CSymbol *getSymbol() const { return name; }
	boost::flyweight<std::string> &getString() const { return name->getString(); }
	CTypeSymbol *getTypeSymbol() const { return type; }

	friend inline bool operator==(const ISymbol& lhs, const ISymbol& rhs);

private:
    CTypeSymbol *type;
	CSymbol *name;
    // Coordinates coordinates;
};


inline bool operator==(const ISymbol& lhs, const ISymbol& rhs) {
	return( lhs.getString() == rhs.getString() );
}

}