#!/bin/bash
# runtime comparison for parallel and sequential versions of Prim's MST
# arguments: 1 - sequential; 2 - concurrent; 3 - numthreads

g++ $1 -std=c++17 -o seq.out
g++ -Xpreprocessor -fopenmp $2 -std=c++17 -lomp -o par.out
TIMEFORMAT=%R
for i in {1..10}
do 
    # echo "Input $i"
    { time ./seq.out < ../input/in$i.in > temp_seq.out ; } 2>> runtime.out
    # echo "sequential"
    { time ./par.out $3 < ../input/in$i.in > temp_par.out ; } 2>> runtime.out
    # echo "parallel"
    diff -b temp_seq.out temp_par.out > diffed.out
    [ -s diffed.out ] && echo "Wrong output test $i"
done

rm ./seq.out
rm ./par.out
rm temp_par.out
rm temp_seq.out
rm diffed.out