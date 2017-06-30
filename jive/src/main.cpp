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
	#define ERR_STREAM std::cerr
#else
	#define ERR_STREAM outfstream
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
		outstreamFolder = "./";

	CJiveEnvironment *jiveEnv = new CJiveEnvironment();

	yyparse( &jiveEnv );

	std::ofstream outfstream;
	std::ostream* outstream = &outfstream;

	outfstream.open( outstreamFolder + "AST_AbstractSyntaxTree.dot", std::ios::out );
	CPrintVisitor printVisitor( jiveEnv, *outstream );
	printVisitor.Start( jiveEnv->program, "my_graph" );
	outfstream.close();

	outfstream.open( outstreamFolder + "ST_SymbolTable.txt", std::ios::out );
	jiveEnv->symbolTable->dump( *outstream );
	outfstream.close();

	outfstream.open( outstreamFolder + "Symbols.txt", std::ios::out );
	CSymbol::dumpStringTable( *outstream );
	outfstream.close();

	CTableCreatorVisitor tableCreatorVisitor( jiveEnv, *outstream );
    tableCreatorVisitor.Start( jiveEnv->program );

	outfstream.open( outstreamFolder + "CE_CompilerErrors.txt", std::ios::out );
	CTypeCheckerVisitor typeCheckerVisitor( jiveEnv, *outstream );
    typeCheckerVisitor.Start( jiveEnv->program );
	outfstream.close();

	outfstream.open( outstreamFolder + "TT_TypeTable.txt", std::ios::out );
	jiveEnv->typeMap->dump( *outstream );
	outfstream.close();

	outfstream.open( outstreamFolder + "CT_ClassTable.txt", std::ios::out );
	jiveEnv->classMap->dump( *outstream );
	outfstream.close();

	return 0;
}