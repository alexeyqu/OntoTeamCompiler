#pragma once
#include <boost/flyweight.hpp>
#include <string>

namespace AST 
{

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

}

namespace std {
    template <>
    struct hash<AST::CSymbol>
    {
        std::hash<std::string> hash_fn;

        std::size_t operator()( const AST::CSymbol &symbol ) const
        {
            return hash_fn( symbol.get() );
        }
    };
}