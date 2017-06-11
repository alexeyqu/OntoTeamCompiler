#!/bin/bash

dot -Tps graph.dot -o graph.ps
dot -Tpng graph.dot -o graph.png