#pragma once

#include <iostream>
#include <cassert>
#include <vector>
#include <unordered_set>
#include "IVisitor.h"
#include "CProgram.h"
#include "Symbols.h"
#include "CX86JiveFrame.h"
#include "Translators.h"
#include "Exps.h"
#include "Stms.h"

namespace AST 
{

using ST::CClassSymbol;
using ST::CMethodSymbol;
using ST::CVariableSymbol;
using ST::CTypeSymbol;

using namespace IRTTRANSLATOR;
using IRT::CX86JiveFrame;
using IRT::CExpList;
using IRT::CStmList;

struct CFragment {
	CFragment( CX86JiveFrame* _frame, IStm* _rootStm, CSymbol *_name ) :
		frame( _frame ), rootStm( _rootStm ), name( _name ) {}

	CX86JiveFrame* frame;
	IStm* rootStm;
	CSymbol *name;
};

class CTranslateVisitor : public IVisitor 
{
public:
	CTranslateVisitor( CJiveEnvironment *_jiveEnv, std::ostream &_outputStream ) : \
		IVisitor( _jiveEnv, _outputStream ) {}
	void Start( IVisitorTarget *vertex );
	
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

	std::vector<CFragment> &getFragments() const { return const_cast<std::vector<CFragment> &>( fragments ); }
	
private:
	CClassSymbol *curClassSymbol;
	CMethodSymbol *curMethodSymbol;
	CX86JiveFrame *curFrame;
	ITranslator *translator;

	std::vector<CFragment> fragments;
	CExpList* expList;
};

}