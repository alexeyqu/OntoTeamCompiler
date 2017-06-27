#pragma once

#include "ISymbol.h"
#include "IVisitorTarget.h"

namespace ST
{

using AST::IVisitorTarget;

class CVariableSymbol : public ISymbol
{
public:
    CVariableSymbol( CSymbol *_name, CTypeSymbol *_type, IVisitorTarget *_vertexAST ) : ISymbol( _name, _type ), vertexAST( _vertexAST ) {}

	IVisitorTarget *vertexAST;
};

}