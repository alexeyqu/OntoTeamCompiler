#pragma once

#include "ISymbol.h"
#include "CSymbol.h"

namespace ST
{

class CTypeSymbol : public ISymbol
{
public:
    CTypeSymbol( CSymbol *_name ) : ISymbol( _name, this ), size( 0 ) {}
	std::size_t getSize() const { return size; }

private:
	std::size_t size;
};

}