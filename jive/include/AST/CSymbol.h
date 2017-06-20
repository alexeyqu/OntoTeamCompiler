#pragma once
#include <boost/flyweight.hpp>
#include <string>

using namespace boost::flyweights;

class CSymbol
{
public:
    CSymbol( std::string _token );
    flyweight<std::string> get() const;

    friend bool operator==( const CSymbol &lhs, const CSymbol &rhs  ) { return lhs.get() == rhs.get(); }

private:
    flyweight<std::string> symbol;
};

namespace std {
    template <>
    struct hash<CSymbol>
    {
        std::hash<std::string> hash_fn;

        std::size_t operator()( const CSymbol &symbol ) const
        {
            return hash_fn( symbol.get() );
        }
    };
}