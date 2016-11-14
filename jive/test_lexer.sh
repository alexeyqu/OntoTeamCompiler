#/bin/bash

cd samples/

for file in *.java ; do
../jive > ../test_results/$file_lexer.txt < $file ; done