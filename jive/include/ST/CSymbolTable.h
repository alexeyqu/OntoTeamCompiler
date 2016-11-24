#pragma once

#include <iostream>
#include <unordered_map>

class CVariable;
class CIdExpression;

class CSymbolTable
{
public:
   CSymbolTable() {}

   void Clear();
   void Insert(CVariable *newVar);
   CVariable *Lookup(CIdExpression *id);
   void Dump();

   std::unordered_map< std::string, CVariable* > table;
}; 