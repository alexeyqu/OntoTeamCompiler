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

namespace std {
    template <>
    struct hash<ST::CSymbol>
    {
        std::hash<std::string> hash_fn;

        std::size_t operator()( const ST::CSymbol &symbol ) const
        {
            return hash_fn( symbol.get() );
        }
    };
}