#include "CSymbolTable.h"

void CSymbolTable::Clear() {
	symbolTable.clear();
}

void CSymbolTable::Insert(CLocalVariable *newVar) {
/*	if( Lookup( newVar->id ) != NULL) {
		std::cout << "Redefinition of " << newVar->id->name << "\n";
	}
*/
	symbolTable.insert({newVar->id->name, newVar});
}

CLocalVariable *CSymbolTable::Lookup(CIdExpression *id) {
	return symbolTable.at(id->name);
}

void CSymbolTable::Dump() {
	std::cout << "\nSymbol table dump\n";
	std::cout << "id\ttype\taddress\n";

	for( auto kv : symbolTable ) {
    	std::cout << kv.first << '\t';

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