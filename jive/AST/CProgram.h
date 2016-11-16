#pragma once

#include "IVisitorTarget.h"
#include "TreeNodes/IStatement.h"
#include "TreeNodes/CBinaryExpression.h"

class CProgram : public IVisitorTarget 
{
public:
	CProgram( IStatement *_statement );

	void Accept( IVisitor *visitor ) override;

	IStatement *statement;
};