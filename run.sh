#!/bin/bash
gcc -Wall -Werror  -o expr expr.c RDP.c TDP.c Tree.c LinkedList.c Stack.c Evaluate.c
./expr
