#/bin/bash

make jive

cd samples/

for file in *.java ; do
../jive > ../test_results/$file.txt < $file ; done