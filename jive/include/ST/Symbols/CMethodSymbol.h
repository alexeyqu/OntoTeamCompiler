#pragma once

#include <vector>
#include <unordered_set>
#include <algorithm>
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

	void insertArgument( CVariableSymbol *argument ) { arguments.push_back( argument ); }
	void insertVariable( CVariableSymbol *variable ) { variables.insert( variable ); }

	std::vector<CVariableSymbol *> &getArguments() { return arguments; }
	int getArgumentsCount() const { return arguments.size(); }
	std::unordered_set<CVariableSymbol *> &getVariables() { return variables; }

	CVariableSymbol *lookupArgument( CVariableSymbol *argument ) { return( std::find( arguments.begin(), arguments.end(), argument ) != arguments.end() ) ? argument : nullptr; }
	CVariableSymbol *lookupVariable( CVariableSymbol *variable ) { return( variables.find( variable ) != variables.end() ) ? variable : nullptr; }
		
	CVariableSymbol *lookupArgument( CSymbol *symbol );
	CVariableSymbol *lookupVariable( CSymbol *symbol );
	
	IVisitorTarget *getVertexAST() const { return vertexAST; }

private:
	std::vector<CVariableSymbol *> arguments;
	std::unordered_set<CVariableSymbol *> variables;

	IVisitorTarget *vertexAST;
};

}