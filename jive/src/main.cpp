#include <iostream>
#include <sstream>
#include <memory>
#include "AST/TreeVisitors/CPrintVisitor.h"
#include "AST/TreeVisitors/CTypeCheckerVisitor.h"
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

    CJiveEnvironment *jiveEnv = new CJiveEnvironment();

    yyparse(&jiveEnv);

    CPrintVisitor printVisitor;
	printVisitor.Start(jiveEnv->program, "my_graph");

    CTypeCheckerVisitor typeCheckerVisitor;
    typeCheckerVisitor.Start(jiveEnv->program);

	return 0;
}