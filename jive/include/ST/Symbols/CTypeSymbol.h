#pragma once

#include "CSymbol.h"

namespace ST
{

class CTypeSymbol 
{
public:
    CTypeSymbol( CSymbol *_name ) : name( _name ), size( 0 ) {}
	std::size_t getSize() const { return size; }

	CSymbol *getSymbol() const { return name; }
	boost::flyweight<std::string> &getString() const { return name->getString(); }

	friend inline bool operator==(const CTypeSymbol& lhs, const CTypeSymbol& rhs);

private:
	CSymbol *name;
	std::size_t size;
};

inline bool operator==(const CTypeSymbol& lhs, const CTypeSymbol& rhs) {
	return( lhs.getString() == rhs.getString() );
}

}