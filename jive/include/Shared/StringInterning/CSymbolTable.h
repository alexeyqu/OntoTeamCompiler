#pragma once
#include <unordered_map>
#include "CSymbol.h"
#include "CType.h"

namespace std 
{
    template <>
    struct hash<ST::CSymbol>
    {
        std::hash<std::string> hash_fn;

        std::size_t operator()( const ST::CSymbol &symbol ) const
        {
            return hash_fn( symbol.getString() );
        }
    };
}

namespace ST 
{

using jive::TType;
using AST::CType;

class CSymbolTable
{
public:
    void insert( CSymbol symbol ) { CSymbol *symbolOwner = new CSymbol( symbol.getString() ); table.insert( std::make_pair( *symbolOwner, CType( TType::UNKNOWNTYPE, symbolOwner ) ) ); }
    void insert( CSymbol symbol, CType type ) { 
		CSymbol *symbolOwner = new CSymbol( symbol.getString() ); 
		CType *typeOwner = new CType( type.getPrimitiveType(), type.getSymbol() );
		table.insert( std::make_pair( *symbolOwner, *typeOwner ) ); 
	}
    void insert( std::string name ) { CSymbol *symbol = new CSymbol( name ); table.insert( std::make_pair( *symbol, CType( TType::UNKNOWNTYPE, symbol ) ) ); }
    std::unordered_map<CSymbol, CType> &get() { return table; }
	void dump( std::ostream &outStream );

	CType lookupType( CSymbol *symbol ) const { return( table.find( *symbol ) != table.end() ) ? table.at( *symbol ) : CType( TType::UNKNOWNTYPE, symbol ); }

private:
    std::unordered_map<CSymbol, CType> table;
};

}
