#include <iostream>
#include <sstream>
#include <memory>
#include "AST/TreeVisitors/CPrintVisitor.h"
#include "AST/TreeVisitors/CTableCreatorVisitor.h"
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

    /*CPrintVisitor printVisitor;
	printVisitor.Start(jiveEnv->program, "my_graph");*/

    CTableCreatorVisitor tableCreatorVisitor;
    tableCreatorVisitor.Start(jiveEnv->program);
    auto table = tableCreatorVisitor.GetTable();
    for( auto classIt : table ) {
        std::cout << "Class " << classIt.first << ":\n";
        std::cout << "Field:\n";
            for( auto varIt : classIt.second->fields ) {
                std::cout << " Field " << varIt.first << " of Type " << varIt.second->type->ToString() << "\n";
            }
        std::cout << "Methods:\n";
        for( auto methodIt : classIt.second->methods ) {
            std::cout << "Method " << methodIt.first << " with return Type " << methodIt.second->type->ToString() << "\n";
            std::cout << "Args:\n";
            for( auto argIt : methodIt.second->arguments ) {
                std::cout << "Arg " << argIt.first << " of Type " << argIt.second->type->ToString() << "\n";
            }
            std::cout << "Vars:\n";
            for( auto varIt : methodIt.second->variables ) {
                std::cout << "Var " << varIt.first << " of Type " << varIt.second->type->ToString() << "\n";
            }
        }
    }
	return 0;
}