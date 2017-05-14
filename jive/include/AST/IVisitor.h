#pragma once

#include "../jive.h"

class CProgram;
class CGoal;
class CBuiltInType;
class CUserType;
class CVariable;
class CCompoundVariable;
class CArgument;
class CCompoundArgument;
class CMethod;
class CCompoundMethod;
class CCompoundClass;
class CMainClass;
class CClass;
class CCompoundStatement;
class CAssignStatement;
class CPrintStatement;
class CIfStatement;
class CWhileStatement;
class CIdExpression;
class CBinaryExpression;
class CNumberExpression;
class CBinaryBooleanExpression;
class CBooleanExpression;
class CThisExpression;
class CNewObjectExpression;
class CNewIntArrayExpression;
class CMethodCallExpression;
class CArrayLengthExpression;
class CArrayIndexExpression;
class CCompoundExpression;

class IVisitor
{
public:
   	virtual void Visit( CProgram *program ) = 0;
   	virtual void Visit( CGoal *goal ) = 0;
   	virtual void Visit( CBuiltInType *type ) = 0;
    virtual void Visit( CUserType *type ) = 0;
   	virtual void Visit( CVariable *entity ) = 0;
    virtual void Visit( CCompoundVariable *entity ) = 0;
    virtual void Visit( CArgument *entity ) = 0;
    virtual void Visit( CCompoundArgument *entity ) = 0;
    virtual void Visit( CMethod *entity ) = 0;
    virtual void Visit( CCompoundMethod *entity ) = 0;
    virtual void Visit( CCompoundClass *entity ) = 0;
    virtual void Visit( CMainClass *entity ) = 0;
    virtual void Visit( CClass *entity ) = 0;
  	virtual void Visit( CCompoundStatement *statement ) = 0;
  	virtual void Visit( CAssignStatement *statement ) = 0;
  	virtual void Visit( CPrintStatement *statement ) = 0;
  	virtual void Visit( CIfStatement *statement ) = 0;
  	virtual void Visit( CWhileStatement *statement ) = 0;
  	virtual void Visit( CIdExpression *expression ) = 0;
  	virtual void Visit( CBinaryExpression *expression ) = 0;
   	virtual void Visit( CNumberExpression *expression ) = 0;
   	virtual void Visit( CBinaryBooleanExpression *expression ) = 0;
   	virtual void Visit( CBooleanExpression *expression ) = 0;   	
   	virtual void Visit( CThisExpression *expression ) = 0;
    virtual void Visit( CNewObjectExpression *expression ) = 0;
    virtual void Visit( CNewIntArrayExpression *expression ) = 0;
    virtual void Visit( CMethodCallExpression *expression ) = 0;
    virtual void Visit( CArrayLengthExpression *expression ) = 0;
    virtual void Visit( CArrayIndexExpression *expression ) = 0;
    virtual void Visit( CCompoundExpression *expression ) = 0;
};