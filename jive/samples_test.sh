#!/bin/bash

FOLDER=test/good_samples
# FOLDER=test/synterrors

cd $FOLDER

mkdir -p ./parsetrees
mkdir -p ./parsetrees/dot
mkdir -p ./symboltables

for f in *.java
do
    echo $f
    ../../jive $f ./parsetrees/dot/$f.dot ./symboltables/$f.txt
    dot -Tps ./parsetrees/dot/$f.dot -o ./parsetrees/$f.ps
    dot -Tpng ./parsetrees/dot/$f.dot -o ./parsetrees/$f.png
done