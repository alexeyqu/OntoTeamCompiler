CPP = g++
FLEX = flex++

all: print_lexemes

print_lexemes:
	$(FLEX) print_lexemes.lex
	$(CPP) lex.yy.cc /usr/lib/libl.a -o print_lexemes

clean:
	rm lex.yy.cc lex.yy.c
