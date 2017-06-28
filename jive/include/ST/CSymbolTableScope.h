// #pragma once
// #include <unordered_map>
// #include "CSymbol.h"
// #include "ISymbol.h"

// namespace ST 
// {

// class CSymbolTableScope
// {
// public:
//     CSymbolTableScope() : scope() {}

//     void insert( ISymbol *symbol ) { scope.insert( std::pair<CSymbol *, ISymbol *>( symbol->name, symbol ) ); }
//     void clear() { scope.clear(); }
//     std::unordered_map<CSymbol *, ISymbol *> &get() { return scope; }

// private:
//     std::unordered_map<CSymbol *, ISymbol *> scope;
// };

// }