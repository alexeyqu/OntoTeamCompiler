#pragma once

#include <unordered_map>
#include <utility>
#include <iostream>
#include "CTypeSymbol.h"
#include "CType.h"

namespace std 
{
    template <>
    struct hash<AST::CType>
    {
        std::hash<std::string> hash_fn;

        std::size_t operator()( const AST::CType &type ) const
        {
            return hash_fn( type.getSymbol()->get() );
        }
    };
}

namespace ST 
{

using AST::CType;

class CTypeTable
{
public:
    CTypeTable();
    void insert( CType *type, CTypeSymbol *symbol ) { table.insert( std::make_pair( *type, *symbol ) ); }
    CTypeSymbol *lookup( CType *type ) { return( table.find( *type ) != table.end() ) ? &table.at( *type ) : nullptr ; }
    std::unordered_map<CType, CTypeSymbol> &get() { return table; }
    void dump();

private:
    std::unordered_map<CType, CTypeSymbol> table;
};

}