#include "IRTree/Temp/CTemp.h"

const std::string CTemp::prefix = "TEMP$";
int CTemp::uniqueId = 0;

CTemp::CTemp() {
	name = prefix + std::to_string( uniqueId );
	uniqueId++;
}

CTemp::CTemp( const CSymbol* symbol ) {
	name = symbol->GetString();
}

const std::string& CTemp::Name() const { 
	return name; 
}

bool CTemp::operator==( const CTemp& other ) const {
    return name == other.name;
}

bool CTemp::operator!=( const CTemp& other ) const {
    return !( *this == other );
}