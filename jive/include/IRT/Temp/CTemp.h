#pragma once

#include "CSymbol.h"

namespace IRT
{

using namespace boost::flyweights;
using ST::CSymbol;

class CTemp
{
public:
    CTemp() : name( tempPrefix + std::to_string( counter++ ) ) {}
    CTemp( CSymbol *symbol ) : name( symbol->getString() ) { counter++; }

    flyweight<std::string> &getString() const { return const_cast<flyweight<std::string> &>( name ); }

    friend bool operator==( const CTemp &lhs, const CTemp &rhs  ) { return lhs.name == rhs.name; }

private:
    flyweight<std::string> name;

    static int counter;

    static const std::string tempPrefix;
};

}

namespace std 
{
    template <>
    struct hash<IRT::CTemp>
    {
        std::hash<std::string> hash_fn;

        std::size_t operator()( const IRT::CTemp &temp ) const
        {
            return hash_fn( temp.getString() );
        }
    };
}