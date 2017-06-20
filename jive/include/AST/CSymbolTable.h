#pragma once
#include <unordered_set>
#include "CSymbol.h"

class CSymbolTable
{
public:
    void insert( CSymbol &symbol ) { table.insert( symbol ); }
    std::unordered_set<CSymbol> &get() { return table; }

private:
    std::unordered_set<CSymbol> table;
};