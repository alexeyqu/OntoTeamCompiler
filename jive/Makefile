CC = g++
LEX = flex++
CFLAGS = --std=c++11

jive: 
	$(LEX) jive.lex
	$(CC) $(CFLAGS) lex.yy.cc -lfl -o jive

clean:
	rm lex.yy.cc jive