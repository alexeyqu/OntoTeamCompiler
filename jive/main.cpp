#include <iostream>
#include <sstream>
#include <memory>
#include "AST/TreeNodes/CBinaryExpression.h"
#include "AST/TreeNodes/CNumberExpression.h"
#include "AST/TreeVisitors/CPrintVisitor.h"
#include "AST/CProgram.h"
#include "jive.tab.h"
#include "jive.lex.h"

int main( int argc, char **argv ) {
    ++argv, --argc;  /* skip over program name */
    if ( argc > 0 )
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;

    CProgram *program;

    yyparse(&program);

    CPrintVisitor printVisitor;
	printVisitor.Start(program, "my_graph");

	return 0;
}