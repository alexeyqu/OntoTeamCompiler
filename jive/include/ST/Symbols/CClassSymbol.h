#pragma once

#include <unordered_set>
#include "CMethodSymbol.h"
#include "CVariableSymbol.h"
#include "ISymbol.h"

namespace ST
{

class CClassSymbol : public ISymbol
{
public:
    CClassSymbol( CSymbol *_name, CTypeSymbol *_type, CClassSymbol *_baseClass  ) : ISymbol( _name, _type ), \
		fields(), methods(), baseClass( _baseClass ) {}

	std::unordered_set<CVariableSymbol *> fields;
	std::unordered_set<CMethodSymbol *> methods;
	CClassSymbol *baseClass;
};

}