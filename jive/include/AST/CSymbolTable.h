#pragma once
#include <unordered_set>
#include "CSymbol.h"

namespace AST 
{

class CSymbolTable
{
public:
    void insert( CSymbol &symbol ) { table.insert( symbol ); }
    void insert( std::string name );
    std::unordered_set<CSymbol> &get() { return table; }

private:
    std::unordered_set<CSymbol> table;
};

}