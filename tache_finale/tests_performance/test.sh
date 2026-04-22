#!/bin/bash
for f in *.pbm;
do
echo "$f: \n"
time ../test_simplification $f
done;