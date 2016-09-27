#/bin/bash

flex++ grammar.lex
g++ lex.yy.cc /usr/lib/libl.a  -o analyzer

cd samples/

for file in *.java ; do
    ../analyzer > ../test_results/$file.txt < $file ; done
