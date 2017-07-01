#pragma once

#include "CSymbol.h"

namespace IRT
{

using namespace boost::flyweights;
using ST::CSymbol;

class CLabel
{
public:
    CLabel() : name( tempPrefix + std::to_string( counter++ ) ) {}
    CLabel( CSymbol *symbol ) : name( symbol->getString() ) { counter++; }

    flyweight<std::string> &getString() const { return const_cast<flyweight<std::string> &>( name ); }
    std::string &getBasicString() const { return const_cast<std::string &>( name.get() ); }

    friend bool operator==( const CLabel &lhs, const CLabel &rhs  ) { return lhs.name == rhs.name; }

private:
    flyweight<std::string> name;

    static int counter;
    static const std::string tempPrefix;
};

}

namespace std 
{
    template <>
    struct hash<IRT::CLabel>
    {
        std::hash<std::string> hash_fn;

        std::size_t operator()( const IRT::CLabel &label ) const
        {
            return hash_fn( label.getString() );
        }
    };
}