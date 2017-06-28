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

	void insertArgument( CVariableSymbol *argument ) { arguments.insert( argument ); }
	void insertVariable( CVariableSymbol *variable ) { variables.insert( variable ); }

	std::unordered_set<CVariableSymbol *> &getArguments() { return arguments; }
	std::unordered_set<CVariableSymbol *> &getVariables() { return variables; }
		
	IVisitorTarget *getVertexAST() const { return vertexAST; }

private:
	std::unordered_set<CVariableSymbol *> arguments;
	std::unordered_set<CVariableSymbol *> variables;

	IVisitorTarget *vertexAST;
};

}