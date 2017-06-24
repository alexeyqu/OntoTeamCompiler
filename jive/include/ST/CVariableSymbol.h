#pragma once

#include "ISymbol.h"

namespace ST
{

class CVariableSymbol : public ISymbol
{
public:
    CVariableSymbol( CTypeSymbol *_type, CSymbol *_name ) : type( _type ), name( _name ) {}
};

}