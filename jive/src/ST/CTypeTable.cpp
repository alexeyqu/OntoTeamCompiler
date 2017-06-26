#include "CTypeTable.h"

namespace ST 
{

void CTypeTable::dump() {
    for( const auto &elem: table ) {
		std::cout << elem.first.getSymbol()->get() << '\t' << elem.second.get()->get() << "\n";
	}
}

}