#pragma once

#include "../jive.h"

class CProgram;
class CAssignStatement;
class CIdExpression;
class CBinaryExpression;
class CNumberExpression;

class IVisitor
{
public:
   	virtual void Visit( CProgram *program ) = 0;
	virtual void Visit( CAssignStatement *statement ) = 0;
	virtual void Visit( CIdExpression *expression ) = 0;
	virtual void Visit( CBinaryExpression *expression ) = 0;
   	virtual void Visit( CNumberExpression *expression ) = 0;
};