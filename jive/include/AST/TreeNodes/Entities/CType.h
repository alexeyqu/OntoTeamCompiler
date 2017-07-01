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
	CType( const CType &other ) : type( other.getPrimitiveType() ), name( other.getSymbol() ) {}

	CSymbol *getSymbol() const { return name; }	
	boost::flyweight<std::string>getString() const { return name->getString(); }
	TType getPrimitiveType() const { return type; }	

	void Accept( IVisitor *visitor ) override { visitor->Visit( this ); }

	friend inline bool operator==(const CType& lhs, const CType& rhs);

private:	
	TType type;
	CSymbol *name;
};

inline bool operator==(const CType& lhs, const CType& rhs) {
	if( lhs.type != rhs.type ) {
		return false;
	}

	if( lhs.type != TType::CLASS ) {
		return true;
	}

	return( lhs.getString() == rhs.getString() );
}

// class CTypeTable
// {
// public:
// 	CTypeTable();		
// 	void insert( CSymbol symbol, TType type ) { types.insert( std::make_pair( symbol, type ) ); }
// 	TType lookup( CSymbol symbol ) { return (types.find( symbol ) != types.end()) ? types.at( symbol ) : UNKNOWNTYPE; }

// 	std::unordered_map<CSymbol, TType> types;
// } typeTable;

// CTypeTable::CTypeTable() {
// 	insert( CSymbol( "int" ), INTEGER );
//     insert( CSymbol( "int[]" ), INTEGERARRAY );
//     insert( CSymbol( "boolean" ), BOOLEAN );
//     insert( CSymbol( "String" ), STRING );
//     insert( CSymbol( "String[]" ), STRINGARRAY );
//     insert( CSymbol( "void" ), VOID );
// }

}