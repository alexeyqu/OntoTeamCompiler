#pragma once

#include <unordered_map>
#include <utility>
#include <iostream>
#include "CTypeSymbol.h"
#include "IType.h"

namespace ST 
{

using AST::IType;

class CTypeTable
{
public:
    void insert( IType *type, CTypeSymbol *symbol ) { table.insert( std::make_pair( *type, *symbol ) ); }
    CTypeSymbol lookup( IType *type ) { /* std::cout << type->getSymbol().get(); dump(); */ return (table.find( *type ) != table.end()) ? table.at( *type ) : nullptr; }
    std::unordered_map<IType, CTypeSymbol> &get() { return table; }
    void dump();

private:
    std::unordered_map<IType, CTypeSymbol> table;
};

}