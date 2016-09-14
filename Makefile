 
CC = g++

CFLAGS = --std=c++11

Compiler: CNumberExpression.o CIdExpression.o CBinaryExpression.o CAssignStatement.o CCompoundStatement.o CPrintVisitor.o CLastExpressionList.o CPrintStatement.o main.o
		$(CC) $(CFLAGS) $^ -o Compiler

main.o: main.cpp
		$(CC) -c $(CFLAGS) $^ -o $@

CNumberExpression.o: CNumberExpression.cpp
		$(CC) -c $(CFLAGS) $^ -o $@

CIdExpression.o: CIdExpression.cpp
		$(CC) -c $(CFLAGS) $^ -o $@

CBinaryExpression.o: CBinaryExpression.cpp
		$(CC) -c $(CFLAGS) $^ -o $@

CAssignStatement.o: CAssignStatement.cpp
		$(CC) -c $(CFLAGS) $^ -o $@

CCompoundStatement.o: CCompoundStatement.cpp
		$(CC) -c $(CFLAGS) $^ -o $@

CPrintVisitor.o: CPrintVisitor.cpp
		$(CC) -c $(CFLAGS) $^ -o $@

CLastExpressionList.o: CLastExpressionList.cpp
		$(CC) -c $(CFLAGS) $^ -o $@

CPrintStatement.o: CPrintStatement.cpp	
		$(CC) -c $(CFLAGS) $^ -o $@