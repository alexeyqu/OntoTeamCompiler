#pragma once

#include <iostream>
#include <cassert>
#include <vector>
#include <unordered_set>
#include "IVisitor.h"
#include "CProgram.h"
#include "Symbols.h"

namespace AST 
{

using ST::CClassSymbol;
using ST::CMethodSymbol;
using ST::CVariableSymbol;
using ST::CTypeSymbol;

class CTypeCheckerVisitor : public IVisitor 
{
public:
	CTypeCheckerVisitor( CJiveEnvironment *_jiveEnv, std::ostream &_outputStream ) : \
		IVisitor( _jiveEnv, _outputStream ), typeError( false ) {}
	void Start( IVisitorTarget *vertex );
	bool failed() const { return typeError; }
	
	void Visit( CProgram *program );
   	void Visit( CGoal *goal );
	void Visit( CType *type );
	void Visit( CVariable *entity );
	void Visit( CCompoundVariable *entity );
	void Visit( CArgument *entity );
	void Visit( CCompoundArgument *entity );
	void Visit( CMethod *entity );
	void Visit( CCompoundMethod *entity );
	void Visit( CCompoundClass *entity );
	void Visit( CMainClass *entity );
	void Visit( CClass *entity );
	void Visit( CCompoundStatement *statement );
	void Visit( CAssignStatement *statement );
	void Visit( CPrintStatement *statement );
	void Visit( CIfStatement *statement );
	void Visit( CWhileStatement *statement );
	void Visit( CIdExpression *expression );
	void Visit( CBinaryExpression *expression );
	void Visit( CNumberExpression *expression );   	
	void Visit( CBinaryBooleanExpression *expression );
   	void Visit( CBooleanExpression *expression );
   	void Visit( CThisExpression *expression );
	void Visit( CNewObjectExpression *expression );
	void Visit( CNewIntArrayExpression *expression );
	void Visit( CMethodCallExpression *expression );
	void Visit( CArrayLengthExpression *expression );
	void Visit( CArrayIndexExpression *expression );
	void Visit( CCompoundExpression *expression );
	void Visit( CVoidExpression *expression );
	
private:
	CClassSymbol *curClassSymbol;
	CMethodSymbol *curMethodSymbol;
	std::vector<CType *> curCallArgTypes;

	bool typeError;
};

}