#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Tree.h"
#include "LinkedList.h"
#include "Stack.h"

extern char* nextInputChar;
extern pStack stack;
extern pNODE root;
extern int paseTable[8][17];

extern bool TDP_MatchTerminal(char c);
extern bool TDP_isTerminal(char c);
extern int s_to_int(char c);
extern int i_to_int(char c);
extern pNODE TDP_Find_Syntactic_Catg(pNODE root);
extern void TDP_Find_Production(int i);
extern void TDP_addProduction(char* c);
extern pNODE TDP_Parse(char* input);