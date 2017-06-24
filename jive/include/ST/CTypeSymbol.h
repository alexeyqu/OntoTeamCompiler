#pragma once

#include "CSymbol.h"

namespace ST
{

class CTypeSymbol : public ISymbol
{
public:
    CTypeSymbol( CSymbol *_name ) : name( _name ), type( this ), size( 0 ) {}
    CSymbol *get() const { return name; }

private:
	std::size size;
};

}