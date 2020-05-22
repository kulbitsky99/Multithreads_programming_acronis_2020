#!/bin/bash
filename=report1.txt
rm -rf $filename
touch $filename
for N in {1..500..1}
do 
    (time ./a.out $N) 2>&1 | grep real >> $filename
done