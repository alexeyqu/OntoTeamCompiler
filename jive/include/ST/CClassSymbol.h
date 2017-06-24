#pragma once

#include <vector>
#include "CMethodSymbol.h"
#include "CVariableSymbol.h"
#include "ISymbol.h"

namespace ST
{

class CClassSymbol : public ISymbol
{
public:
    CClassSymbol( CTypeSymbol *_type, CSymbol *_name, CClassSymbol *_baseClass ) : type( _type ), name( _name ), \
		fields(), methods(), baseClass( _baseClass ) {}

	std::vector<CVariableSymbol *> fields;
	std::vector<CMethodSymbol *> methods;
	CClassSymbol *baseClass;
};

}