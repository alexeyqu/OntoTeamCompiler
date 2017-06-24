#include <iostream>
#include <sstream>
#include <memory>
#include "AST/TreeVisitors/CPrintVisitor.h"
#include "AST/CProgram.h"
#include "CJiveEnvironment.h"
#include "jive.tab.h"
#include "jive.lex.h"

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
	CPrintVisitor printVisitor( outstream );
	printVisitor.Start( jiveEnv->program, "my_graph" );
	outstream.close();

	outstream.open( outstreamFolder + "ST.txt", std::ios::out ); // TODO print results in good way
	for( const auto &elem: jiveEnv->symbolTable->get() ) {
		outstream << &elem << '\t' << elem.get() << "\n";
	}
	outstream.close();

	return 0;
}