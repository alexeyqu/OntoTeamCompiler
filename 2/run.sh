#/bin/bash

flex++ grammar.lex
g++ lex.yy.cc -lfl -o analyzer