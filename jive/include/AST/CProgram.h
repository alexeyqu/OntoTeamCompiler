#pragma once

#include "IVisitorTarget.h"
#include "AST/TreeNodes/Types.h"
#include "AST/TreeNodes/Entities.h"
#include "AST/TreeNodes/Statements.h"
#include "AST/TreeNodes/Expressions.h"

namespace AST 
{

class CProgram : public IVisitorTarget 
{
public:
	CProgram( IVisitorTarget *_rootVertex ) : rootVertex( _rootVertex ) {}

	void Accept( IVisitor *visitor ) override { visitor->Visit(this); }

	IVisitorTarget *getRoot() const { return rootVertex; }

private:
	IVisitorTarget *rootVertex;
};

}