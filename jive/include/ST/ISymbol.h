#pragma once

#include "../AST/TreeNodes/IType.h"
#include <string>
#include "../AST/Coordinates.h"
#include "CSymbol.h"

class ISymbol {
public:
	ISymbol( std::string _name, IType* _type ) {
		name = CSymbol::GetSymbol( _name );
		type =  _type;
	}
	const std::string& GetName() const { return name->GetString(); }

	CSymbol* name;
	IType* type;
	Coordinates coordinates;
};