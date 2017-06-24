#pragma once
#include <unordered_set>
#include "CSymbol.h"

namespace ST 
{

class CSymbolTableScope
{
public:
    void insert( CSymbol *symbol ) { scope.insert( symbol ); }
    std::unordered_set<CSymbol *> &get() { return scope; }

private:
    std::unordered_set<CSymbol *> scope;
};

}