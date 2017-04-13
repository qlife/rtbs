#!/bin/sh
gcc -std=c11 -g -o english-numbers english-numbers.c
./english-numbers 1 2 12 13 19 20 21 22 25 89 189 15625 9,999,999,999 2,147,483,647 999,999,999,999 1_3_5_7_9
