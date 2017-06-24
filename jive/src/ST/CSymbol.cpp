#include "CSymbol.h"

namespace ST 
{

CSymbol::CSymbol( std::string _token ) : symbol( _token ) {}

flyweight<std::string> CSymbol::get() const { return symbol; }

}