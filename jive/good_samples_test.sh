#!/bin/bash

FOLDER=test

cd $FOLDER

mkdir -p ./good_results

cd ./good_samples

for f in *.java
do
    echo $f
    mkdir -p ../good_results/$f
    cp $f ../good_results/$f/code.java
    ../../jive $f ../good_results/$f/
    # dot -Tps ../good_results/$f/AST_AbstractSyntaxTree.dot -o ../good_results/$f/AST_AbstractSyntaxTree.ps
    # dot -Tpng ../good_results/$f/AST_AbstractSyntaxTree.dot -o ../good_results/$f/AST_AbstractSyntaxTree.png
    dot -Tps ../good_results/$f/IR_IRTree.dot -o ../good_results/$f/IR_IRTree.ps
    dot -Tpng ../good_results/$f/IR_IRTree.dot -o ../good_results/$f/IR_IRTree.png
done