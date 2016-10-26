#/bin/bash

cd samples/

for file in *.java ; do
    ../print_lexemes > ../test_results/$file.txt < $file ; done
