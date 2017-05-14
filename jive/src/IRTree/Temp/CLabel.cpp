#include "IRTree/Temp/CLabel.h"

int CLabel::uniqueId = 0;
const std::string CLabel::prefix = "LABEL$";

CLabel::CLabel() {
	name = prefix + std::to_string( uniqueId );
	uniqueId++;
}

CLabel::CLabel( const CSymbol* symbol ) {
	name = symbol->GetString();
}

const std::string& CLabel::Name() const { 
	return name; 
}

bool CLabel::operator==( const CLabel& other ) const {
    return name == other.name;
}

bool CLabel::operator!=( const CLabel& other ) const {
    return !( *this == other );
}