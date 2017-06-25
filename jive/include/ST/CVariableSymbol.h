#pragma once

#include "ISymbol.h"

namespace ST
{

class CVariableSymbol : public ISymbol
{
public:
    CVariableSymbol( CTypeSymbol *_type, CSymbol *_name ) : ISymbol( _type, _name ) {}
};

}