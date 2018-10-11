#!/bin/bash
g++ ./Source/Source.cpp -o Lab2
echo -e '\n_______\nTest 1:'
cat ./Tests/Test1.txt
echo -e '\n_______\nTesting:\n'
./Lab2 < ./Tests/Test1.txt
echo -e ''
echo -e '\n_______\nTest 2:'
cat ./Tests/Test2.txt
echo -e '\n_______\nTesting:\n'
./Lab2 < ./Tests/Test2.txt
echo -e ''
echo -e '\n_______\nTest 3:'
cat ./Tests/Test3.txt
echo -e '\n_______\nTesting:\n'
./Lab2 < ./Tests/Test3.txt
echo -e ''
echo -e '\n_______\nTest 4:'
cat ./Tests/Test4.txt
echo -e '\n_______\nTesting:\n'
./Lab2 < ./Tests/Test4.txt
echo -e ''
echo -e '\n_______\nTest 5:'
cat ./Tests/Test5.txt
echo -e '\n_______\nTesting:\n'
./Lab2 < ./Tests/Test5.txt
echo -e ''
echo -e '\n_______\nTest 6:'
cat ./Tests/Test6.txt
echo -e '\n_______\nTesting:\n'
./Lab2 < ./Tests/Test6.txt
echo -e ''
echo -e '\n_______\nTest 7:'
cat ./Tests/Test7.txt
echo -e '\n_______\nTesting:\n'
./Lab2 < ./Tests/Test7.txt

