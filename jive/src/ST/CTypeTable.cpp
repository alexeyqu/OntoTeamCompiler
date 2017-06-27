#include "CTypeTable.h"

namespace ST 
{

using jive::TType;

CTypeTable::CTypeTable() {
	CSymbol *typeSymbol = nullptr;

	typeSymbol = new CSymbol( "int" );
	table.insert( std::make_pair( CType( TType::INTEGER, typeSymbol ), CTypeSymbol( typeSymbol ) ) );
	typeSymbol = new CSymbol( "int[]" );
	table.insert( std::make_pair( CType( TType::INTEGERARRAY, typeSymbol ), CTypeSymbol( typeSymbol ) ) );
	typeSymbol = new CSymbol( "boolean" );
	table.insert( std::make_pair( CType( TType::BOOLEAN, typeSymbol ), CTypeSymbol( typeSymbol ) ) );
	typeSymbol = new CSymbol( "String" );
	table.insert( std::make_pair( CType( TType::STRING, typeSymbol ), CTypeSymbol( typeSymbol ) ) );
	typeSymbol = new CSymbol( "String[]" );
	table.insert( std::make_pair( CType( TType::STRINGARRAY, typeSymbol ), CTypeSymbol( typeSymbol ) ) );
	typeSymbol = new CSymbol( "void" );
	table.insert( std::make_pair( CType( TType::VOID, typeSymbol ), CTypeSymbol( typeSymbol ) ) );
}

void CTypeTable::dump() {
    for( const auto &elem: table ) {
		std::cout << elem.first.getSymbol()->get() << '\t' << elem.second.get()->get() << "\n";
	}
}

}