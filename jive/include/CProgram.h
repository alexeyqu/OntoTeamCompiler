#pragma once

#include "AST/IVisitorTarget.h"
#include "AST/TreeNodes/Entities.h"
#include "AST/TreeNodes/Statements.h"
#include "AST/TreeNodes/Expressions.h"
#include "TypeChecker/CSymbolTable.h"

class CProgram : public IVisitorTarget 
{
public:
	CProgram( IVisitorTarget *_rootVertex );

	void Accept( IVisitor *visitor ) override;

	IVisitorTarget *rootVertex;
	CSymbolTable *symbolTable;
};