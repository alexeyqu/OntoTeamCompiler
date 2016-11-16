CC = g++
LEX = flex
CFLAGS = --std=c++11 # -lasan -O -g -fsanitize=address -fno-omit-frame-pointer

jive: jive.tab.o lex.yy.o AST/CProgram.o AST/TreeNodes/Statements/CCompoundStatement.o AST/TreeNodes/Statements/CPrintStatement.o AST/TreeNodes/Statements/CAssignStatement.o AST/TreeNodes/Expressions/CIdExpression.o AST/TreeNodes/Expressions/CNumberExpression.o AST/TreeNodes/Expressions/CBinaryExpression.o AST/TreeVisitors/CPrintVisitor.o main.o
	$(CC) $(CFLAGS) $^ -lfl -o $@

main.o: main.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

lex.yy.o: jive.lex
	$(LEX) --header-file=jive.lex.h jive.lex
	$(CC) $(CFLAGS) -c lex.yy.c -o $@

jive.tab.o: jive.y
	bison -d -v jive.y
	$(CC) $(CFLAGS) -c jive.tab.c -o $@

AST/CProgram.o: AST/CProgram.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

AST/TreeNodes/Statements/CCompoundStatement.o: AST/TreeNodes/Statements/CCompoundStatement.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

AST/TreeNodes/Statements/CAssignStatement.o: AST/TreeNodes/Statements/CAssignStatement.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

AST/TreeNodes/Statements/CPrintStatement.o: AST/TreeNodes/Statements/CPrintStatement.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

AST/TreeNodes/Expressions/CIdExpression.o: AST/TreeNodes/Expressions/CIdExpression.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

AST/TreeNodes/Expressions/CBinaryExpression.o: AST/TreeNodes/Expressions/CBinaryExpression.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

AST/TreeNodes/Expressions/CNumberExpression.o: AST/TreeNodes/Expressions/CNumberExpression.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

AST/TreeVisitors/CPrintVisitor.o: AST/TreeVisitors/CPrintVisitor.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm lex.yy.* *.lex.h jive.tab.* jive *.o AST/TreeNodes/*.o AST/TreeNodes/*.o AST/TreeNodes/Statements/*.o AST/TreeVisitors/*.o AST/*.o *.ps