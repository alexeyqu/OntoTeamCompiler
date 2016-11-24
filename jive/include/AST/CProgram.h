#pragma once

#include "IVisitorTarget.h"
#include "TreeNodes/CEntities.h"
#include "TreeNodes/CStatements.h"
#include "TreeNodes/CExpressions.h"

class CProgram : public IVisitorTarget 
{
public:
	CProgram( IVisitorTarget *_rootVertex );

	void Accept( IVisitor *visitor ) override;

	IVisitorTarget *rootVertex;
};