#include "CSymbolTable.h"

namespace ST
{

void CSymbolTable::dump( std::ostream &outStream ) {
	for( const auto &elem: table ) {
		outStream << &elem << '\t' << elem.first.getString() << '\t' << elem.second.getString() << "\n";
	}
}

}