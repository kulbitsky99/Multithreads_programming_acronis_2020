#!/bin/bash
rm -rf report.txt
touch report.txt
for N in {1..300..1}
do 
    (time ./a.out $N) 2>&1 | grep real >> report.txt
done
