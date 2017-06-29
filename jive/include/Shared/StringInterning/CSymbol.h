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

    flyweight<std::string> &getString() const { return const_cast<flyweight<std::string> &>( symbol ); }

    friend bool operator==( const CSymbol &lhs, const CSymbol &rhs  ) { return lhs.symbol == rhs.symbol; }

private:
    flyweight<std::string> symbol;
};

}