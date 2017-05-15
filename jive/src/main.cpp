#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include "AST/TreeVisitors/CPrintVisitor.h"
#include "AST/TreeVisitors/CTableCreatorVisitor.h"
#include "AST/TreeVisitors/CTypeCheckerVisitor.h"
#include "AST/TreeVisitors/CTranslateVisitor.h"
#include "IRTree/TreeVisitors/CIRTreePrinter.h"
#include "IRTree/CCanonizer.h"
#include "CJiveEnvironment.h"
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

    yyparse( &jiveEnv );

    /*std::ofstream outstream;
    outstream.open( "graph.dot", std::ios::out );
    CPrintVisitor printVisitor( outstream );
	printVisitor.Start( jiveEnv->program, "my_graph" );
    outstream.close();*/

	CSymbolsTable* table = new CSymbolsTable();
    CTableCreatorVisitor tableCreatorVisitor( table );
    tableCreatorVisitor.Start(jiveEnv->program);
    CTypeCheckerVisitor typeCheckerVisitor( table );
    typeCheckerVisitor.Start(jiveEnv->program);
	CTranslateVisitor translateVisitor( table );
	translateVisitor.Start(jiveEnv->program);
	std::vector<CFragment> fragments = translateVisitor.Fragments;
	std::map<CFragment*, CStmList*> canonizedFragments;
	for ( auto& fragment : fragments ) {			
		CCanonizer canonizer( fragment.rootStm, fragment.frame );
		canonizer.Canonize();
		canonizedFragments[&fragment] = canonizer.GetCanonizedStms();
	}
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
    outstream.open( "symbolTable.txt", std::ios::out );
    for( auto classIt : table ) {
        outstream << "Class " << classIt.first << ":\n";
        outstream << "\tFields:\n";
            for( auto varIt : classIt.second->fields ) {
                outstream << "\t\tField " << varIt.first << " : " << varIt.second->type->ToString() << "\n";
            }
        outstream << "\tMethods:\n";
        for( auto methodIt : classIt.second->methods ) {
            outstream << "\t\t" << methodIt.first << " : " << methodIt.second->type->ToString() << "\n";
            outstream << "\t\t\tArgs:\n";
            for( auto argIt : methodIt.second->arguments ) {
                outstream << "\t\t\t\t" << argIt.first << " : " << argIt.second->type->ToString() << "\n";
            }
            outstream << "\t\t\tVars:\n";
            for( auto varIt : methodIt.second->variables ) {
                outstream << "\t\t\t\t" << varIt.first << " : " << varIt.second->type->ToString() << "\n";
            }
        }

<<<<<<< HEAD
        std::cout << "---\n\n";
    }*/
	return 0;
}