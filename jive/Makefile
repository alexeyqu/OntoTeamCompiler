SHELL = /bin/sh

CC = g++-4.8
CFLAGS = --std=c++11 -O -g -fsanitize=address -fno-omit-frame-pointer -MD
LIBS = -lasan -lfl
OBJS = AST/CProgram.o \
	AST/TreeNodes/Statements/CCompoundStatement.o AST/TreeNodes/Statements/CPrintStatement.o AST/TreeNodes/Statements/CAssignStatement.o \
	AST/TreeNodes/Statements/CIfStatement.o \
	AST/TreeNodes/Expressions/CIdExpression.o AST/TreeNodes/Expressions/CNumberExpression.o AST/TreeNodes/Expressions/CBinaryExpression.o \
	AST/TreeNodes/Expressions/CBooleanExpression.o AST/TreeNodes/Expressions/CBinaryBooleanExpression.o \
	AST/TreeNodes/Expressions/CThisExpression.o \
	AST/TreeVisitors/CPrintVisitor.o main.o

 .SUFFIXES:   
 .SUFFIXES: .cpp .o   

jive: jive.tab.o lex.yy.o $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

asan: jive.tab.o lex.yy.o $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@ && \
	ASAN_OPTIONS=symbolize=1 ASAN_SYMBOLIZER_PATH=$(SHELL which llvm-symbolizer-3.8) ./jive_asan

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $*.o

lex.yy.o: jive.lex
	flex --header-file=jive.lex.h jive.lex
	$(CC) $(CFLAGS) -c lex.yy.c -o $@

jive.tab.o: jive.y
	bison -d -v jive.y
	$(CC) $(CFLAGS) -c jive.tab.c -o $@

clean:
	rm -f lex.yy.* *.lex.h jive.tab.* jive jive_asan *.ps
	find . -name '*.o' -delete
	find . -name '*.d' -delete