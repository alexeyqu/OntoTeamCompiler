CC = g++
LEX = flex
CFLAGS = --std=c++11 # -lasan -O -g -fsanitize=address -fno-omit-frame-pointer

jive: jive.tab.o lex.yy.o AST/CProgram.o AST/TreeNodes/CNumberExpression.o AST/TreeNodes/CBinaryExpression.o AST/TreeNodes/CPrintVisitor.o main.o
	$(CC) $(CFLAGS) $^ -lfl -o $@

main.o: main.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

lex.yy.o: jive.lex
	$(LEX) --header-file=jive.lex.h jive.lex
	$(CC) $(CFLAGS) -c lex.yy.c -o $@

jive.tab.o: jive.y
	bison -d -v jive.y
	$(CC) $(CFLAGS) -c jive.tab.c -o $@

AST/TreeNodes/CNumberExpression.o: AST/TreeNodes/CNumberExpression.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

AST/TreeNodes/CBinaryExpression.o: AST/TreeNodes/CBinaryExpression.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

AST/TreeNodes/CPrintVisitor.o: AST/TreeVisitors/CPrintVisitor.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

AST/CProgram.o: AST/CProgram.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm lex.yy.* *.lex.h jive.tab.* jive *.o AST/TreeNodes/*.o AST/TreeVisitors/*.o AST/*.o *.ps