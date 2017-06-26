#pragma once
#include <boost/flyweight.hpp>
#include <string>

namespace ST 
{

using namespace boost::flyweights;

class CSymbol
{
public:
    CSymbol( std::string _token ) : symbol( _token ) {}
    flyweight<std::string> get() const { return symbol; }

    friend bool operator==( const CSymbol &lhs, const CSymbol &rhs  ) { return lhs.get() == rhs.get(); }

private:
    flyweight<std::string> symbol;
};

}