#!/bin/bash
# poprawione z OKI: https://www.youtube.com/watch?v=kusMkfEutJE
a=1
#echo Kompilowanie brut...
#g++ pla.d.cpp -o brut -O3 -static -std=c++17
echo Kompilowanie wzor...
g++ pla.cpp -o wzor -O3 -static -std=c++17

cp ocen-linux/in/pla0.in test.in
while true; do
    echo Wzor...
    time ./wzor < test.in > wzor.out
    echo Brut...
    time ./brut < test.in > brut.out
    if diff wzor.out brut.out -B -I -w -E -y -Z; then
        echo "$a [OK]"
    else
        echo "$a [FAIL]"
        exit 1
    fi
    a=$(( a+1 ))
    echo Gen...
    ./gen.py > test.in
done
