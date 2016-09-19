#/bin/bash

flex++ grammar.lex
g++ lex.yy.cc -lfl -o analyzer

cd samples/

for file in *.java ; do
    ../analyzer > ../test_results/$file.txt < $file ; done
