#pragma once

#include <iostream>
#include <unordered_map>

class CClass;
class CIdExpression;

class CUserClassTable
{
public:
   CUserClassTable() {}

   void Clear();
   void Insert( CClass* userClass );
   CClass *Lookup( CIdExpression *id );

   std::unordered_map< std::string, CClass* > table;
};  
