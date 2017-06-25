#pragma once

#include "CSymbol.h"

namespace ST
{

class CTypeSymbol;

class ISymbol
{
public:
    ISymbol( CTypeSymbol *_type, CSymbol *_name ) : type( _type ), name( _name ) {}

    CTypeSymbol *type;
	CSymbol *name;
};

}