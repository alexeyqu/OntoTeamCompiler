#/bin/bash

flex grammar.lex
gcc lex.yy.c -lfl -o analyzer
