#pragma once

class CSymbolTable
{
public:
	std::map<std::string, CClassSymbol *> table;
};