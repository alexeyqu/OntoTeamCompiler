#pragma once

#include <string>
#include <unordered_map>
#include "IVisitorTarget.h"
#include "CSymbol.h"

namespace AST 
{

using ST::CSymbol;
using jive::TType;

class CType : public IVisitorTarget 
{
public:
	CType( TType _type, CSymbol *_name ) : type( _type ), name( _name ) {}

	CSymbol *getSymbol() const { return name; }	
	TType getType() const { return type; }	

	void Accept( IVisitor *visitor ) override;

private:	
	TType type;
	CSymbol *name;
};

inline bool operator==(const CType& lhs, const CType& rhs) {
	TType type1 = lhs.getType(), type2 = rhs.getType();

	if( type1 != type2 ) {
		return false;
	}

	if( type1 != TType::CLASS ) {
		return true;
	}

	return( lhs.getSymbol()->get() == rhs.getSymbol()->get() );
}

// class CTypeTable
// {
// public:
// 	CTypeTable();		
// 	void insert( CSymbol symbol, TType type ) { types.insert( std::make_pair( symbol, type ) ); }
// 	TType lookup( CSymbol symbol ) { return (types.find( symbol ) != types.end()) ? types.at( symbol ) : UNKNOWNTYPE; }

// 	std::unordered_map<CSymbol, TType> types;
// } typeTable;

}