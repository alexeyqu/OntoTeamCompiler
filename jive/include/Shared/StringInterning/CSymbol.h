#pragma once
#include <boost/flyweight.hpp>
#include <string>
#include <unordered_map>

namespace ST 
{

using namespace boost::flyweights;

class CSymbol
{
public:
    flyweight<std::string> &getString() const { return const_cast<flyweight<std::string> &>( symbol ); }

    friend bool operator==( const CSymbol &lhs, const CSymbol &rhs  ) { return lhs.symbol == rhs.symbol; }

	static CSymbol *makeSymbol( const std::string& token );

	static void dumpStringTable( std::ostream &outputStream );

private:
    CSymbol( std::string _token ) : symbol( _token ) {}

    flyweight<std::string> symbol;
	static std::unordered_map<flyweight<std::string>, CSymbol *> stringTable; 
};

}