#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "LinkedList.h"

typedef struct Stack *pStack;
struct Stack;

extern pStack Stack_new();

extern bool Stack_is_empty(pStack stack);

extern void Stack_push(pStack stack, char* data);

extern char* Stack_pop(pStack stack);

extern void Stack_free(pStack stack);

