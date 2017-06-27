#pragma once

#include <unordered_set>
#include "CMethodSymbol.h"
#include "CVariableSymbol.h"
#include "ISymbol.h"
#include "IVisitorTarget.h"
#include "CMethod.h"
#include "CVariable.h"

namespace ST
{

using AST::IVisitorTarget;
using AST::CVariable;
using AST::CMethod;

class CClassSymbol : public ISymbol
{
public:
    CClassSymbol( CSymbol *_name, CTypeSymbol *_type, CClassSymbol *_baseClass, IVisitorTarget *_vertexAST ) : ISymbol( _name, _type ), \
		fields(), methods(), baseClass( _baseClass ), vertexAST( _vertexAST ) {}

	CMethodSymbol *lookupMethod( CMethod *method );
	CVariableSymbol *lookupField( CVariable *method );

	std::unordered_set<CVariableSymbol *> fields;
	std::unordered_set<CMethodSymbol *> methods;
	CClassSymbol *baseClass;

	IVisitorTarget *vertexAST;
};

}