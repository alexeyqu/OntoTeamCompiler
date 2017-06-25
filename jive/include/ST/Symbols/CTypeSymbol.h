#pragma once

#include "ISymbol.h"
#include "CSymbol.h"

namespace ST
{

class CTypeSymbol : public ISymbol
{
public:
    CTypeSymbol( CSymbol *_name ) : ISymbol( _name, this ), size( 0 ) {}
    CSymbol *get() const { return name; }

private:
	std::size_t size;
};

}