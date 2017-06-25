#pragma once

#include "ISymbol.h"

namespace ST
{

class CVariableSymbol : public ISymbol
{
public:
    CVariableSymbol( CSymbol *_name, CTypeSymbol *_type ) : ISymbol( _name, _type ) {}
};

}