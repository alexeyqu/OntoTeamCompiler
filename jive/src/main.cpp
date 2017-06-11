#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include "AST/TreeVisitors/CPrintVisitor.h"
#include "ST/Visitors/CTableCreatorVisitor.h"
#include "ST/Visitors/CTypeCheckerVisitor.h"
#include "../include/CJiveEnvironment.h"
#include "CProgram.h"
#include "jive.tab.h"
#include "jive.lex.h"

int main( int argc, char **argv ) {
	++argv, --argc;  /* skip over program name */
	if ( argc > 0 )
		yyin = fopen( argv[0], "r" );
	else
		yyin = stdin;

	std::string outstreamDotPath;
	if ( argc > 1 )
		outstreamDotPath = argv[1];
	else
		outstreamDotPath = "graph.dot";

	std::string outstreamSTPath;
	if ( argc > 2 )
		outstreamSTPath = argv[2];
	else
		outstreamSTPath = "symbolTable.txt";

	CJiveEnvironment *jiveEnv = new CJiveEnvironment();

	yyparse( &jiveEnv );

	std::ofstream outstream;
	outstream.open( outstreamDotPath, std::ios::out );
	CPrintVisitor printVisitor( outstream );
	printVisitor.Start( jiveEnv->program, "my_graph" );
	outstream.close();

	CSymbolTable *symbolTable = new CSymbolTable();

	CTableCreatorVisitor tableCreatorVisitor( symbolTable );
	tableCreatorVisitor.Start(jiveEnv->program);

	CTypeCheckerVisitor typeCheckerVisitor( symbolTable );
	typeCheckerVisitor.Start(jiveEnv->program);
	
	outstream.open( outstreamSTPath, std::ios::out );
	for( auto classIt : symbolTable->table ) {
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

		outstream << "---\n\n";
	}
	outstream.close();

	return 0;
}