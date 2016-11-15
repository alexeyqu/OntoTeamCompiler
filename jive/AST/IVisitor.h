#pragma once

#include "../jive.h"

class IVisitorTarget;
class CBinaryExpression;
class CNumberExpression;
class CProgram;

class IVisitor
{
public:
   	virtual void Visit( CProgram* ) = 0;
	virtual void Visit( CBinaryExpression* ) = 0;
   	virtual void Visit( CNumberExpression* ) = 0;
};