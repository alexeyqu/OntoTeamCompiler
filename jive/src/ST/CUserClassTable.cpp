#include "CUserClassTable.h"

#include "CClass.h"
#include "CIdExpression.h"

void CUserClassTable::Clear() {
   table.clear();
}

void CUserClassTable::Insert( CClass *newClass ) {
   table.insert( { newClass->name->name, newClass } );
}

CClass *CUserClassTable::Lookup( CIdExpression *id ) {
  std::cout << id->name;
  return table.at( id->name );
}