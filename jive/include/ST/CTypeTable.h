#pragma once

#include <unordered_set>
#include "CTypeSymbol.h"

namespace ST 
{

class CTypeTable
{
public:
    void insert( CTypeSymbol *symbol ) { table.insert( symbol ); }
    std::unordered_set<CTypeSymbol *> &get() { return table; }

private:
    std::unordered_set<CTypeSymbol *> table;
};

}