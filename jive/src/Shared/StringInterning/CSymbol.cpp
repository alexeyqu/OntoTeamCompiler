#include "CSymbol.h"

namespace ST
{

CSymbol *CSymbol::makeSymbol( const std::string& token ) {
	flyweight<std::string> internedToken = flyweight<std::string>( token );
	auto result = stringTable.find( internedToken );
	if (result == stringTable.end()) {
		CSymbol *symbol = new CSymbol( internedToken );
		stringTable[internedToken] = symbol;
		return symbol;
	} else {
		return result->second;
	}
}

void CSymbol::dumpStringTable( std::ostream &outputStream ) {
	for( const auto &elem: stringTable ) {		
		outputStream << elem.first << '\t' << elem.second->getString() << "\n";
	}
}


std::unordered_map<flyweight<std::string>, CSymbol *> CSymbol::stringTable;

}