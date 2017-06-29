#include "CClassMap.h"

namespace ST
{

CClassSymbol *CClassMap::lookup( CSymbol *name ) {
    for( auto classTuple : table ) {
        if( classTuple.first->getString() == name->getString() ) {
            return classTuple.second;
        }
    }

    return nullptr;
}

void CClassMap::dump( std::ostream &outStream ) {
	for( auto classTuple : table ) {
		auto classSymbol = classTuple.second;
		outStream << "Class " << classSymbol->getString();
		if( classSymbol->getBaseClass() != nullptr ){
			outStream << " : public " << classSymbol->getBaseClass()->getString() << "\n";
		} else {
			outStream << "\n";
		}

		outStream << "Fields:\n";
		for( auto varSymbol : classSymbol->getFields() ) {
			outStream << "\tField " << varSymbol->getString() << " of Type " << varSymbol->getTypeSymbol()->getString() << "\n";
		}

		outStream << "Methods:\n";
		for( auto methodSymbol : classSymbol->getMethods() ) {
			outStream << "Method " << methodSymbol->getString() << " with return Type " << methodSymbol->getTypeSymbol()->getString() << "\n";

			outStream << "\tArgs:\n";
			for( auto argSymbol : methodSymbol->getArguments() ) {
				outStream << "\t\tArg " << argSymbol->getString() << " of Type " << argSymbol->getTypeSymbol()->getString() << "\n";
			}
			
			outStream << "\tVars:\n";
			for( auto varSymbol : methodSymbol->getVariables() ) {
				outStream << "\t\tVar " << varSymbol->getString() << " of Type " << varSymbol->getTypeSymbol()->getString() << "\n";
			}
		}
		outStream << "---\n\n";
	}
}

}