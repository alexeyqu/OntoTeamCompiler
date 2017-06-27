#pragma once
#include <unordered_set>
#include "CSymbol.h"

namespace std 
{
    template <>
    struct hash<ST::CSymbol>
    {
        std::hash<std::string> hash_fn;

        std::size_t operator()( const ST::CSymbol &symbol ) const
        {
            return hash_fn( symbol.get() );
        }
    };
}

namespace ST 
{

class CSymbolTable
{
public:
    void insert( CSymbol symbol ) { table.insert( symbol ); }
    void insert( std::string name );
    // CSymbol *lookup( std::string name ) { CSymbol tmp( name ); return( table.find(  ) != table.end() ) ? &table.at( *type ) : nullptr ; }
    std::unordered_set<CSymbol> &get() { return table; }

private:
    std::unordered_set<CSymbol> table;
};

}
