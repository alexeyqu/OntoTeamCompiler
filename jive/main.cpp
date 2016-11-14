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
	printVisitor.Start(program, "graph.dot", "graph1");
}
/*
int main( int argc, char **argv ) {
 
	

			buffer.str( "" );
			std::cout << "Point 7\n";
			std::unique_ptr<CProgram> program = std::unique_ptr<CProgram>(cProgram);
			std::cout << "Point 8\n";
			// CPrintVisitor visitor = CPrintVisitor();
			CConvertVisitor visitor = CConvertVisitor();
			std::cout << "Point 9\n";
			std::cout << program.get() << "\n";
			program->Accept(visitor);
			std::cout << "Point 10\n";
			std::string result = visitor.GetResult();
			std::cout << "Point 11\n";
			std::ofstream out(std::to_string(i) + "res.java", std::fstream::out);
			out << result;
			out.close();
		}
	}

	return 0;
	/*  CNumberExpression five(5);
	  CNumberExpression three(3);
	  CBinaryExpression sum(&five, CBinaryExpression::OT_Plus, &three);

	  CPrintVisitor printVisitor;
	  printVisitor.Start(&sum, "graph1.dot", "graph1");

	  return 0;
}*/