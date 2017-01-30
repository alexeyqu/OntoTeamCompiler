#/bin/bash

cd test/synterrors

for f in *.java
do
    echo $f
    ../../jive < $f
done
