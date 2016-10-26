CC = g++
FLEX = flex++
CFLAGS = --std=c++11

all: print_lexemes

print_lexemes:
	$(FLEX) print_lexemes.lex
	$(CC) $(CFLAGS) lex.yy.cc /usr/lib/libl.a -o print_lexemes

clean:
	rm lex.yy.cc print_lexemes
