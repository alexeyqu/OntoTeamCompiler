#!/bin/bash

mkdir -p test/parsetrees
mkdir -p test/parsetrees/dot

cd test/samples

for f in *.java
do
    echo $f
    ../../Debug/jive < $f > ../parsetrees/dot/$f.dot
  #  dot -Tps ../parsetrees/dot/$f.dot -o ../parsetrees/$f.ps
    dot -Tpng ../parsetrees/dot/$f.dot -o ../parsetrees/dot/$f.png
done