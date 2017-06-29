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

	void insertField( CVariableSymbol *field ) { fields.insert( field ); }
	void insertMethod( CMethodSymbol *method ) { methods.insert( method ); }

	std::unordered_set<CVariableSymbol *> &getFields() { return fields; }
	std::unordered_set<CMethodSymbol *> &getMethods() { return methods; }
	CClassSymbol *getBaseClass() const { return baseClass; }
	void setBaseClass( CClassSymbol *_baseClass ) { baseClass = _baseClass; }

	CMethodSymbol *lookupMethod( CMethod *method );
	CVariableSymbol *lookupField( CVariable *field );

	CMethodSymbol *lookupMethod( CSymbol *method );
	CVariableSymbol *lookupField( CSymbol *field );

	CMethodSymbol *lookupMethod( CMethodSymbol *method ) { return( methods.find( method ) != methods.end() ) ? method : nullptr; }
	CVariableSymbol *lookupField( CVariableSymbol *field ) { return( fields.find( field ) != fields.end() ) ? field : nullptr; }

private:
	std::unordered_set<CVariableSymbol *> fields;
	std::unordered_set<CMethodSymbol *> methods;
	CClassSymbol *baseClass;

	IVisitorTarget *vertexAST;
};

}