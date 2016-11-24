#include "CSymbolTable.h"

#include "CVariable.h"
#include "CIdExpression.h"

void CSymbolTable::Clear() {
   table.clear();
}

void CSymbolTable::Insert(CVariable *newVar) {
/* if( Lookup( newVar->id ) != NULL) {
       std::cout << "Redefinition of " << newVar->id->name << "\n";
   }
*/
   table.insert({newVar->id->name, newVar});
}

CVariable *CSymbolTable::Lookup(CIdExpression *id) {
  std::cout << id->name;
  return table.at(id->name);
}

void CSymbolTable::Dump() {
   std::cout << "\nSymbol table dump\n";
   std::cout << "id\ttype\taddress\n";

   for( auto kv : table ) {
       std::cout << "'" << kv.first << "'\t";

       switch(kv.second->type->type) {
           case enums::INTEGER:
               std::cout << "INT" << '\t';
               break;

           case enums::BOOLEAN:
               std::cout << "BOOL" << '\t';
               break;
       }
         
        std::cout << kv.second << "\n";
   }   

   std::cout << "\n";
} 