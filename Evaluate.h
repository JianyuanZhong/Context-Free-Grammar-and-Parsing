#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Tree.h"
#include "RDP.h"

//extern bool Use_Result;

extern bool isDigit(char c);
extern bool isOperator(char c);
extern double evaluate_Tree(pNODE root);
extern double evaluate_N(pNODE root);
extern double evaluate_F(pNODE root,double result);
extern double evaluate_T(pNODE root, double result);