#pragma once

#include <iostream>
#include <unordered_map>
#include "../AST/TreeNodes/Expressions.h"
#include "../AST/TreeNodes/Entities.h"

class CSymbolTable
{
public:
	CSymbolTable() {}

	void Clear();
	void Insert(CLocalVariable *newVar);
	CLocalVariable *Lookup(CIdExpression *id);
	void Dump();

	std::unordered_map< std::string, CLocalVariable* > symbolTable;
};