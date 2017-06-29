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
            return hash_fn( type.getString() );
        }
    };

	template <>
    struct hash<ST::CTypeSymbol>
    {
        std::hash<std::string> hash_fn;

        std::size_t operator()( const ST::CTypeSymbol &typeSymbol ) const
        {
            return hash_fn( typeSymbol.getString() );
        }
    };
}

namespace ST 
{

using AST::CType;

class CTypeMap
{
public:
    CTypeMap();
    void insert( CType *type, CTypeSymbol *symbol ) { tableTypeSymbol.insert( std::make_pair( *type, *symbol ) ); tableType.insert( std::make_pair( *symbol, *type ) ); }
    CTypeSymbol *lookup( CType *type ) { return( tableTypeSymbol.find( *type ) != tableTypeSymbol.end() ) ? &tableTypeSymbol.at( *type ) : nullptr ; }
    CType *lookup( CTypeSymbol *symbol ) { return( tableType.find( *symbol ) != tableType.end() ) ? &tableType.at( *symbol ) : nullptr ; }
	// CType *lookup( jive::TType primitiveType );
    std::unordered_map<CType, CTypeSymbol> &get() { return tableTypeSymbol; }

	void dump( std::ostream &outStream );
	
private:
    std::unordered_map<CType, CTypeSymbol> tableTypeSymbol;
    std::unordered_map<CTypeSymbol, CType> tableType;
};

}