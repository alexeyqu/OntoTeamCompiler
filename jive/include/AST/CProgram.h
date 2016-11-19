#pragma once

#include "IVisitorTarget.h"
#include "TreeNodes/Entities.h"
#include "TreeNodes/Statements.h"
#include "TreeNodes/Expressions.h"

class CProgram : public IVisitorTarget 
{
public:
	CProgram( IVisitorTarget *_rootVertex );

	void Accept( IVisitor *visitor ) override;

	IVisitorTarget *rootVertex;
};