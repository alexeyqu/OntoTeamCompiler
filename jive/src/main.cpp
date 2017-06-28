#include <iostream>
#include <sstream>
#include <fstream>
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

#ifdef _DEBUG
	#define TCH_STREAM std::cerr
#else
	#define TCH_STREAM outfstream
#endif

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

	std::ofstream outfstream;
	std::ostream* outstream = &outfstream;

	outfstream.open( outstreamFolder + "AST_AbstractSyntaxTree.dot", std::ios::out );
	CPrintVisitor printVisitor( jiveEnv, *outstream );
	printVisitor.Start( jiveEnv->program, "my_graph" );
	outfstream.close();

	outfstream.open( outstreamFolder + "ST_SymbolTable.txt", std::ios::out );
	for( const auto &elem: jiveEnv->symbolTable->get() ) {
		*outstream << &elem << '\t' << elem.getString() << "\n";
	}
	outfstream.close();

	CTableCreatorVisitor tableCreatorVisitor( jiveEnv, *outstream );
    tableCreatorVisitor.Start( jiveEnv->program );
	
	outfstream.open( outstreamFolder + "TT_TypeTable.txt", std::ios::out );
	for( const auto &elem: jiveEnv->typeTable->get() ) {
		*outstream << elem.first.getString() << '\t' << elem.second.getString() << "\n";
	}
	outfstream.close();

	outfstream.open( outstreamFolder + "CT_ClassTable.txt", std::ios::out );
	for( auto classTuple : jiveEnv->classTable->get() ) {
		auto classSymbol = classTuple.second;
		*outstream << "Class " << classSymbol->getString();
		if( classSymbol->getBaseClass() != nullptr ){
			*outstream << " : public " << classSymbol->getBaseClass()->getString() << "\n";
		} else {
			*outstream << "\n";
		}

		*outstream << "Fields:\n";
		for( auto varSymbol : classSymbol->getFields() ) {
			*outstream << "\tField " << varSymbol->getString() << " of Type " << varSymbol->getTypeSymbol()->getString() << "\n";
		}

		*outstream << "Methods:\n";
		for( auto methodSymbol : classSymbol->getMethods() ) {
			*outstream << "Method " << methodSymbol->getString() << " with return Type " << methodSymbol->getTypeSymbol()->getString() << "\n";

			*outstream << "\tArgs:\n";
			for( auto argSymbol : methodSymbol->getArguments() ) {
				*outstream << "\t\tArg " << argSymbol->getString() << " of Type " << argSymbol->getTypeSymbol()->getString() << "\n";
			}
			
			*outstream << "\tVars:\n";
			for( auto varSymbol : methodSymbol->getVariables() ) {
				*outstream << "\t\tVar " << varSymbol->getString() << " of Type " << varSymbol->getTypeSymbol()->getString() << "\n";
			}
		}
		*outstream << "---\n\n";
	}
	outfstream.close();

	outfstream.open( outstreamFolder + "CE_CompilerErrors.txt", std::ios::out );
	outstream = &TCH_STREAM;
	CTypeCheckerVisitor typeCheckerVisitor( jiveEnv, *outstream );
    typeCheckerVisitor.Start( jiveEnv->program );
	outfstream.close();

	return 0;
}