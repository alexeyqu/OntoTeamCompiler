#pragma once

#include "../jive.h"

class CProgram;
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

class IVisitor
{
public:
   	virtual void Visit( CProgram *program ) = 0;
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
};