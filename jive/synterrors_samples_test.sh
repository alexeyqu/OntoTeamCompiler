#!/bin/bash

FOLDER=test

cd $FOLDER

mkdir -p ./synterrors_results

cd ./synterrors_samples

for f in *.java
do
    echo $f
    mkdir -p ../synterrors_results/$f
    cp $f ../synterrors_results/$f/code.java
    ../../jive $f ../synterrors_results/$f/
    # dot -Tps ../good_results/$f/AST_AbstractSyntaxTree.dot -o ../good_results/$f/AST_AbstractSyntaxTree.ps
    # dot -Tpng ../good_results/$f/AST_AbstractSyntaxTree.dot -o ../good_results/$f/AST_AbstractSyntaxTree.png
done