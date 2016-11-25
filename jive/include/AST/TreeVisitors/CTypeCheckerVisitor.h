#pragma once

#include <iostream>
#include <cassert>
#include "../CProgram.h"

class CTypeCheckerVisitor : public IVisitor 
{
public:
	void Start( IVisitorTarget *vertex );
	
	void Visit( CProgram *program );
   	void Visit( CGoal *goal );
	void Visit( CBuiltInType *type );
	void Visit( CUserType *type );
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
}; 
 
