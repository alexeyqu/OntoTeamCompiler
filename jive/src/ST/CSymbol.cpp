#include "ST/CSymbol.h"

CSymbol* CSymbol::GetSymbol( const std::string& key ) {
	auto result = stringTable.find( key );
	if (result == stringTable.end()) {
		CSymbol *symbol = new CSymbol( key );
		stringTable[key] = symbol;
		return symbol;
	} else {
		return result->second;
	}
}

const std::string& CSymbol::GetString() const { 
	return stringKey; 
}

std::unordered_map<std::string, CSymbol*> CSymbol::stringTable;