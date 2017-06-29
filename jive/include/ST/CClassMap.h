#pragma once

#include <unordered_set>
#include <utility>
#include <iostream>
#include "CClassSymbol.h"	
#include "CClass.h"

// namespace std 
// {
//     template <>
//     struct hash<AST::CClass>
//     {
//         std::hash<std::string> hash_fn;

//         std::size_t operator()( const AST::CClass &_class ) const
//         {
//             return hash_fn( _class.name->getName() );
//         }
//     };
// }

namespace ST 
{

using AST::CClass;

class CClassMap
{
public:
    CClassMap() {}
    void insert( CClass *_class, CClassSymbol *_symbol ) { table.insert( std::make_pair( _class, _symbol ) ); }
    CClassSymbol *lookup( CClass *_class ) { return( table.find( _class ) != table.end() ) ? table.at( _class ) : nullptr ; }
    CClassSymbol *lookup( CSymbol *name );
    // CClass *lookupClass( CSymbol *name );
    std::unordered_map<CClass *, CClassSymbol *> &get() { return table; }

    void dump( std::ostream &outStream );

private:
    std::unordered_map<CClass *, CClassSymbol *> table;
};

}