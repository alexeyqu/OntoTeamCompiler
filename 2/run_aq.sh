#/bin/bash

rm *.tab.c *.tab.h lex.yy.c

bison -d grammar.y
flex lexer.lex
gcc lex.yy.c grammar.tab.c /usr/lib/libl.a -o analyzer
