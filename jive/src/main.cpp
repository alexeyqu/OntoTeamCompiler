#include <iostream>
#include <sstream>
#include <memory>
#include "AST/TreeVisitors/CPrintVisitor.h"
#include "AST/TreeVisitors/CTableCreatorVisitor.h"
#include "AST/TreeVisitors/CTypeCheckerVisitor.h"
#include "AST/TreeVisitors/CTranslateVisitor.h"
#include "IRTree/TreeVisitors/CIRTreePrinter.h"
#include "../include/CJiveEnvironment.h"
#include "AST/CProgram.h"
#include "jive.tab.h"

extern FILE* yyin;

int main( int argc, char **argv ) {
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;

    CJiveEnvironment *jiveEnv = new CJiveEnvironment();

    yyparse(&jiveEnv);

    /*CPrintVisitor printVisitor;
	printVisitor.Start(jiveEnv->program, "my_graph");*/

	CSymbolsTable* table = new CSymbolsTable();
    CTableCreatorVisitor tableCreatorVisitor( table );
    tableCreatorVisitor.Start(jiveEnv->program);
    CTypeCheckerVisitor typeCheckerVisitor( table );
    typeCheckerVisitor.Start(jiveEnv->program);
	CTranslateVisitor translateVisitor( table );
	translateVisitor.Start(jiveEnv->program);
	std::vector<CFragment> fragments = translateVisitor.Fragments;
	CIRTreePrinter *irTreePrinter;
	irTreePrinter = new CIRTreePrinter( "ir-tree.dot" );
	irTreePrinter->OpenFile();

	size_t methodsCounter = 1;
	for( auto& method : fragments ) {
		irTreePrinter->ResetPrinter( "fragment" + std::to_string( methodsCounter ) + "_", method.name );
		method.rootStm->Accept( irTreePrinter );
		methodsCounter += 1;
		irTreePrinter->WriteGraphToFile();
	}
	irTreePrinter->CloseFile();
    /*
    for( auto classIt : table ) {
        std::cout << "Class " << classIt.first << ":\n";
        std::cout << "Fields:\n";
            for( auto varIt : classIt.second->fields ) {
                std::cout << "\tField " << varIt.first << " of Type " << varIt.second->type->ToString() << "\n";
            }
        std::cout << "Methods:\n";
        for( auto methodIt : classIt.second->methods ) {
            std::cout << "Method " << methodIt.first << " with return Type " << methodIt.second->type->ToString() << "\n";
            std::cout << "\tArgs:\n";
            for( auto argIt : methodIt.second->arguments ) {
                std::cout << "\t\tArg " << argIt.first << " of Type " << argIt.second->type->ToString() << "\n";
            }
            std::cout << "\tVars:\n";
            for( auto varIt : methodIt.second->variables ) {
                std::cout << "\t\tVar " << varIt.first << " of Type " << varIt.second->type->ToString() << "\n";
            }
        }

        std::cout << "---\n\n";
    }*/
	return 0;
}