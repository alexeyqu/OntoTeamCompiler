#include <iostream>
#include <sstream>
#include <memory>
#include "AST/TreeVisitors/CPrintVisitor.h"
#include "AST/TreeVisitors/CTableCreatorVisitor.h"
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

    /*CPrintVisitor printVisitor;
	printVisitor.Start(jiveEnv->program, "my_graph");*/

    CTableCreatorVisitor tableCreatorVisitor;
    tableCreatorVisitor.Start(jiveEnv->program);
    auto table = tableCreatorVisitor.GetTable();
    CTypeCheckerVisitor typeCheckerVisitor( table );
    typeCheckerVisitor.Start(jiveEnv->program);
    /*
    for( auto classIt : table ) {
        std::cout << "Class " << classIt.first << ":\n";
        std::cout << "Fields:\n";
            for( auto varIt : classIt.second->fields ) {
                std::cout << "\tField " << varIt.first << " of Type " << varIt.second->type->ToString() << "\n";
            }
        std::cout << "Methods:\n";
        for( auto methodIt : classIt.second->methods ) {
            std::cout << "Method " << methodIt.first << " with return Type " << methodIt.second->type->ToString() << "\n";
            std::cout << "\tArgs:\n";
            for( auto argIt : methodIt.second->arguments ) {
                std::cout << "\t\tArg " << argIt.first << " of Type " << argIt.second->type->ToString() << "\n";
            }
            std::cout << "\tVars:\n";
            for( auto varIt : methodIt.second->variables ) {
                std::cout << "\t\tVar " << varIt.first << " of Type " << varIt.second->type->ToString() << "\n";
            }
        }

        std::cout << "---\n\n";
    }*/

	return 0;
}