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
	outstream.open( outstreamFolder + "AST_AbstractSyntaxTree.dot", std::ios::out );
	CPrintVisitor printVisitor( jiveEnv, outstream );
	printVisitor.Start( jiveEnv->program, "my_graph" );
	outstream.close();

	outstream.open( outstreamFolder + "ST_SymbolTable.txt", std::ios::out );
	for( const auto &elem: jiveEnv->symbolTable->get() ) {
		outstream << &elem << '\t' << elem.get() << "\n";
	}
	outstream.close();

	CTableCreatorVisitor tableCreatorVisitor( jiveEnv, outstream );
    tableCreatorVisitor.Start( jiveEnv->program );
	
	outstream.open( outstreamFolder + "TT_TypeTable.txt", std::ios::out );
	for( const auto &elem: jiveEnv->typeTable->get() ) {
		outstream << elem.first.getSymbol()->get() << '\t' << elem.second.get()->get() << "\n";
	}
	outstream.close();

	outstream.open( outstreamFolder + "CT_ClassTable.txt", std::ios::out );
	for( auto classTuple : jiveEnv->classTable->get() ) {
		auto classSymbol = classTuple.second;
		outstream << "Class " << classSymbol->name->get();
		if( classSymbol->baseClass != nullptr ){
			outstream << " : public " << classSymbol->baseClass->name->get() << "\n";
		} else {
			outstream << "\n";
		}

		outstream << "Fields:\n";
		for( auto varSymbol : classSymbol->fields ) {
			outstream << "\tField " << varSymbol->name->get() << " of Type " << varSymbol->type->get()->get() << "\n";
		}

		outstream << "Methods:\n";
		for( auto methodSymbol : classSymbol->methods ) {
			outstream << "Method " << methodSymbol->name->get() << " with return Type " << methodSymbol->type->get()->get() << "\n";

			outstream << "\tArgs:\n";
			for( auto argSymbol : methodSymbol->arguments ) {
				outstream << "\t\tArg " << argSymbol->name->get() << " of Type " << argSymbol->type->get()->get() << "\n";
			}
			
			outstream << "\tVars:\n";
			for( auto varSymbol : methodSymbol->variables ) {
				outstream << "\t\tVar " << varSymbol->name->get() << " of Type " << varSymbol->type->get()->get() << "\n";
			}
		}
		outstream << "---\n\n";
	}
	outstream.close();

	outstream.open( outstreamFolder + "CE_CompilerErrors.txt", std::ios::out );
	CTypeCheckerVisitor typeCheckerVisitor( jiveEnv, outstream );
    typeCheckerVisitor.Start( jiveEnv->program );
	outstream.close();

	return 0;
}