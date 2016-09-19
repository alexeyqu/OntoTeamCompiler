#/bin/bash

flex grammar.lex
gcc lex.yy.c -lfl -o analyzer

cd samples/

for file in *.java ; do
    ../analyzer > ../test_results/$file.txt < $file ; done
