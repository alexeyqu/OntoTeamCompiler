#pragma once

#include <unordered_set>
#include "CVariableSymbol.h"
#include "ISymbol.h"
#include "IVisitorTarget.h"

namespace ST
{

using AST::IVisitorTarget;

class CMethodSymbol : public ISymbol
{
public:
    CMethodSymbol( CSymbol *_name, CTypeSymbol *_type, IVisitorTarget *_vertexAST ) : ISymbol( _name, _type ), arguments(), variables(), vertexAST( _vertexAST ) {}

	std::unordered_set<CVariableSymbol *> arguments;
	std::unordered_set<CVariableSymbol *> variables;

	IVisitorTarget *vertexAST;
};

}