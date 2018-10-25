#!/bin/bash
./compile.sh
echo -e '\n_______\nTest 1:'
cat ./tests/test1.txt
echo -e '\n_______\nTesting:\n'
./lab3 < ./tests/test1.txt
echo -e ''
echo -e '\n_______\nTest 2:'
cat ./tests/test2.txt
echo -e '\n_______\nTesting:\n'
./lab3 < ./tests/test2.txt
echo -e ''
echo -e '\n_______\nTest 3:'
cat ./tests/test3.txt
echo -e '\n_______\nTesting:\n'
./lab3 < ./tests/test3.txt
echo -e ''
echo -e '\n_______\nTest 4:'
cat ./tests/test4.txt
echo -e '\n_______\nTesting:\n'
./lab3 < ./tests/test4.txt
echo -e ''
echo -e '\n_______\nTest 5:'
cat ./tests/test5.txt
echo -e '\n_______\nTesting:\n'
./lab3 < ./tests/test5.txt
echo -e ''
