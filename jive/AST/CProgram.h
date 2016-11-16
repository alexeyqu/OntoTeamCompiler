#pragma once

#include "IVisitorTarget.h"
#include "TreeNodes/Statements.h"
#include "TreeNodes/Expressions.h"

class CProgram : public IVisitorTarget 
{
public:
	CProgram( IStatement *_statement );

	void Accept( IVisitor *visitor ) override;

	IStatement *statement;
};