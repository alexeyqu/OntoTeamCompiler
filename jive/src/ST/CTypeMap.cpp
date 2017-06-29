#include "CTypeMap.h"

namespace ST 
{

using jive::TType;

CTypeMap::CTypeMap() {
	CSymbol *typeSymbol = nullptr;

	typeSymbol = new CSymbol( "int" );
	tableTypeSymbol.insert( std::make_pair( CType( TType::INTEGER, typeSymbol ), CTypeSymbol( typeSymbol ) ) );
	tableType.insert( std::make_pair( CTypeSymbol( typeSymbol ), CType( TType::INTEGER, typeSymbol ) ) );
	typeSymbol = new CSymbol( "int[]" );
	tableTypeSymbol.insert( std::make_pair( CType( TType::INTEGERARRAY, typeSymbol ), CTypeSymbol( typeSymbol ) ) );
	tableType.insert( std::make_pair( CTypeSymbol( typeSymbol ), CType( TType::INTEGERARRAY, typeSymbol ) ) );
	typeSymbol = new CSymbol( "boolean" );
	tableTypeSymbol.insert( std::make_pair( CType( TType::BOOLEAN, typeSymbol ), CTypeSymbol( typeSymbol ) ) );
	tableType.insert( std::make_pair( CTypeSymbol( typeSymbol ), CType( TType::BOOLEAN, typeSymbol ) ) );
	typeSymbol = new CSymbol( "String" );
	tableTypeSymbol.insert( std::make_pair( CType( TType::STRING, typeSymbol ), CTypeSymbol( typeSymbol ) ) );
	tableType.insert( std::make_pair( CTypeSymbol( typeSymbol ), CType( TType::STRING, typeSymbol ) ) );
	typeSymbol = new CSymbol( "String[]" );
	tableTypeSymbol.insert( std::make_pair( CType( TType::STRINGARRAY, typeSymbol ), CTypeSymbol( typeSymbol ) ) );
	tableType.insert( std::make_pair( CTypeSymbol( typeSymbol ), CType( TType::STRINGARRAY, typeSymbol ) ) );
	typeSymbol = new CSymbol( "void" );
	tableTypeSymbol.insert( std::make_pair( CType( TType::VOID, typeSymbol ), CTypeSymbol( typeSymbol ) ) );
	tableType.insert( std::make_pair( CTypeSymbol( typeSymbol ), CType( TType::VOID, typeSymbol ) ) );
}

void CTypeMap::dump( std::ostream &outStream ) {
	for( const auto &elem: tableTypeSymbol ) {		
		outStream << elem.first.getString() << '\t' << elem.second.getString() << "\n";
	}
}

}