#pragma once

#include "../jive.h"

class CBinaryExpression;
class CNumberExpression;
class CProgram;

class IVisitor
{
public:
   	virtual void Visit( CProgram *program ) = 0;
	virtual void Visit( CBinaryExpression *expression ) = 0;
   	virtual void Visit( CNumberExpression *expression ) = 0;
};