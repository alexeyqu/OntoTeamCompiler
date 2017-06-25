#include <iostream>
#include <sstream>
#include <memory>
#include <unordered_set>
#include "AST/TreeVisitors/CPrintVisitor.h"
#include "AST/TreeVisitors/CTypeCheckerVisitor.h"
#include "AST/TreeVisitors/CTableCreatorVisitor.h"
#include "AST/CProgram.h"
#include "CJiveEnvironment.h"
#include "ST/Symbols/CClassSymbol.h"
#include "jive.tab.h"
#include "jive.lex.h"

using ST::CClassSymbol;

int main( int argc, char **argv ) {
	++argv, --argc;  /* skip over program name */
	if ( argc > 0 ) /* get code */
		yyin = fopen( argv[0], "r" );
	else
		yyin = stdin;

	std::string outstreamFolder;
	if ( argc > 1 ) /* output folder */
		outstreamFolder = argv[1];
	else
		outstreamFolder = ".";

	CJiveEnvironment *jiveEnv = new CJiveEnvironment();

	yyparse( &jiveEnv );

	std::ofstream outstream;
	outstream.open( outstreamFolder + "AST.dot", std::ios::out );
	CPrintVisitor printVisitor( jiveEnv, outstream );
	printVisitor.Start( jiveEnv->program, "my_graph" );
	outstream.close();

	outstream.open( outstreamFolder + "ST.txt", std::ios::out );
	for( const auto &elem: jiveEnv->symbolTable->get() ) {
		outstream << elem << '\t' << elem->get() << "\n";
	}
	outstream.close();

	CTableCreatorVisitor tableCreatorVisitor( jiveEnv );
    tableCreatorVisitor.Start( jiveEnv->program );
	std::unordered_set<CClassSymbol *> classTable = tableCreatorVisitor.getClassTable();

	outstream.open( outstreamFolder + "TT.txt", std::ios::out );
	for( const auto &elem: jiveEnv->typeTable->get() ) {
		outstream << elem.first->getSymbol().get() << '\t' << elem.second->get()->get() << "\n";
	}
	outstream.close();

	for( auto classSymbol : classTable ) {
		std::cout << "Class " << classSymbol->name->get() << ":\n";

		std::cout << "Fields:\n";
		for( auto varSymbol : classSymbol->fields ) {
			std::cout << "\tField " << varSymbol->name->get() << " of Type " << varSymbol->type << "\n";
		}

		std::cout << "Methods:\n";
		for( auto methodSymbol : classSymbol->methods ) {
			std::cout << "Method " << methodSymbol->name->get() << " with return Type " << methodSymbol->type << "\n";

			std::cout << "\tArgs:\n";
			for( auto argSymbol : methodSymbol->arguments ) {
				std::cout << "\t\tArg " << argSymbol->name->get() << " of Type " << argSymbol->type << "\n";
			}
			
			std::cout << "\tVars:\n";
			for( auto varSymbol : methodSymbol->variables ) {
				std::cout << "\t\tVar " << varSymbol->name->get() << " of Type " << varSymbol->type << "\n";
			}
		}
		std::cout << "---\n\n";
	}

	CTypeCheckerVisitor typeCheckerVisitor( jiveEnv, classTable );
    typeCheckerVisitor.Start( jiveEnv->program );

	return 0;
}