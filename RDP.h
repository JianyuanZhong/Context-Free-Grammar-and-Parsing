#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Tree.h"

extern char *nextInputChar;
extern pNODE root;

extern pNODE RDP_new(char *input);
extern bool RDP_Look_Ahead(char c);
extern int RDP_Match_Terminal(char c);
extern bool isDigit(char c);
extern pNODE E();
extern pNODE TT();
extern pNODE T();
extern pNODE FT();
extern pNODE F();
extern pNODE N();
extern pNODE NT();
extern pNODE D();