
#pragma once

#include <iostream>
#include <cassert>
#include <fstream>
#include "CProgram.h"

namespace AST 
{

class CPrintVisitor : public IVisitor 
{
public:
	CPrintVisitor( CJiveEnvironment *_jiveEnv, std::ofstream &_outputStream ) : IVisitor( _jiveEnv ), outputStream( _outputStream ) {};

	void Start( IVisitorTarget *vertex, std::string graphname );
	
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
	
private:
	std::size_t generateId( void *entity );
	std::ofstream &outputStream;
};

}