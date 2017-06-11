#/bin/bash

cd test/synterrors

OUT=../../synterrors.log

echo "" > $OUT

for f in *.java
do
    echo "\t" $f >> $OUT
    ../../jive < $f >> $OUT 2>&1
done
