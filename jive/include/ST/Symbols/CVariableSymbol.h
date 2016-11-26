#pragma once

#include "ISymbol.h"

class CVariableSymbol : public ISymbol {

public:
	CVariableSymbol( std::string _name, IType* _type ) : ISymbol( _name, _type ) {}
};