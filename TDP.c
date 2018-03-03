#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Tree.h"
#include "TDP.h"
#include "LinkedList.h"
#include "Stack.h"

char *nextInputChar;
pStack stack;
pNODE root;
int paseTable[8][17] = {
        //    {0 , 1,  2, 3, 4, 5, 6, 7, 8, 9, +, -, *, /, (, ), e}
        /*E*/ {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        /*T*/
              {4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4},
        /*TT*/
              {1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  3,  1,  1,  1,  1},
        /*F*/
              {8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  -1, -1, -1, -1, 9,  -1},
        /*FT*/
              {5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  6,  7,  5,  5},
        /*N*/
              {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, -1, -1, -1, -1, -1, -1},
        /*NT*/
              {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, -1, -1, -1, -1, -1, 11},
        /*D*/
              {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, -1, -1, -1, -1, -1, -1},
};

bool TDP_MatchTerminal(char c) {
    if (*nextInputChar == c) {
        nextInputChar++;
        return true;
    }
        return false;

}





bool TDP_isTerminal(char c) {
    switch (c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
        case 'e':
            return true;
        default:
            false;
    }
    return false;
}



int s_to_int(char c) {
    switch (c) {
        case 'E':
            return 0;
        case 'T':
            return 1;
        case 't':
            return 2;
        case 'F':
            return 3;
        case 'f':
            return 4;
        case 'N':
            return 5;
        case 'n':
            return 6;
        case 'D':
            return 7;
        default:
            return -1;
    }
}

int i_to_int(char c) {

    if(c=='\n') return -1;

    switch (c) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case '+':
            return 10;
        case '-':
            return 11;
        case '*':
            return 12;
        case '/':
            return 13;
        case '(':
            return 14;
        case ')':
            return 15;
        case '\0':
            return 0;
        default :
            return 100;
    }
}

pNODE TDP_Find_Syntactic_Catg(pNODE root) {

    if (Tree_get_LMC(root) != NULL) {
        pNODE temp = TDP_Find_Syntactic_Catg(Tree_get_LMC(root));
        if (temp != NULL) return temp;
    } else if(!TDP_isTerminal(Tree_get_data(root))){
        return root;
    }

    if(Tree_get_RS(root)!=NULL){
        pNODE temp1 = TDP_Find_Syntactic_Catg(Tree_get_RS(root));
        if (temp1 != NULL) return temp1;
    }
    return NULL;
}

void TDP_Find_Production(int i) {
    pNODE node = TDP_Find_Syntactic_Catg(root);
    pNODE tp1, tp2, tp3;
    switch (i) {

        case -1:
            while(!Stack_is_empty(stack)){
                Stack_pop(stack);
            }
            root = NULL;
            break;
        case 0:
            Stack_push(stack, "t");
            Stack_push(stack, "T");

            Tree_set_LMC(node, Tree_new_Node('T'));
            Tree_set_RS(Tree_get_LMC(node), Tree_new_Node('t'));
            break;
        case 1:
            Stack_push(stack, "e");
            Tree_set_LMC(node, Tree_new_Node('e'));
            break;
        case 2:
            Stack_push(stack, "t");
            Stack_push(stack, "T");
            Stack_push(stack, "+");
            tp1 = Tree_new_Node('+');
            tp2 = Tree_new_Node('T');
            tp3 = Tree_new_Node('t');
            Tree_set_LMC(node, tp1);
            Tree_set_RS(tp1, tp2);
            Tree_set_RS(tp2, tp3);
            break;
        case 3:
            Stack_push(stack, "t");
            Stack_push(stack, "T");
            Stack_push(stack, "-");
            tp1 = Tree_new_Node('-');
            tp2 = Tree_new_Node('T');
            tp3 = Tree_new_Node('t');
            Tree_set_LMC(node, tp1);
            Tree_set_RS(tp1, tp2);
            Tree_set_RS(tp2, tp3);
            break;
        case 4:
            Stack_push(stack, "f");
            Stack_push(stack, "F");
            Tree_set_LMC(node, Tree_new_Node('F'));
            Tree_set_RS(Tree_get_LMC(node), Tree_new_Node('f'));
            break;
        case 5:
            Stack_push(stack, "e");
            Tree_set_LMC(node, Tree_new_Node('e'));
            break;
        case 6:
            Stack_push(stack, "f");
            Stack_push(stack, "F");
            Stack_push(stack, "*");
            tp1 = Tree_new_Node('*');
            tp2 = Tree_new_Node('F');
            tp3 = Tree_new_Node('f');
            Tree_set_LMC(node, tp1);
            Tree_set_RS(tp1, tp2);
            Tree_set_RS(tp2, tp3);
            break;
        case 7:
            Stack_push(stack, "f");
            Stack_push(stack, "F");
            Stack_push(stack, "/");
            tp1 = Tree_new_Node('/');
            tp2 = Tree_new_Node('F');
            tp3 = Tree_new_Node('f');
            Tree_set_LMC(node, tp1);
            Tree_set_RS(tp1, tp2);
            Tree_set_RS(tp2, tp3);
            break;
        case 8:
            Stack_push(stack, "N");
            Tree_set_LMC(node, Tree_new_Node('N'));
            break;
        case 9:
            Stack_push(stack, ")");
            Stack_push(stack, "E");
            Stack_push(stack, "(");
            tp1 = Tree_new_Node('(');
            tp2 = Tree_new_Node('E');
            tp3 = Tree_new_Node(')');
            Tree_set_LMC(node, tp1);
            Tree_set_RS(tp1, tp2);
            Tree_set_RS(tp2, tp3);
            break;
        case 10:
            Stack_push(stack, "n");
            Stack_push(stack, "D");
            Tree_set_LMC(node, Tree_new_Node('D'));
            Tree_set_RS(Tree_get_LMC(node), Tree_new_Node('n'));
            break;
        case 11:
            Stack_push(stack, "e");
            Tree_set_LMC(node, Tree_new_Node('e'));
            break;
        case 12:
            Stack_push(stack, "N");
            Tree_set_LMC(node, Tree_new_Node('N'));
            break;
        case 13:
            Stack_push(stack, "0");
            Tree_set_LMC(node, Tree_new_Node('0'));
            break;
        case 14:
            Stack_push(stack, "1");
            Tree_set_LMC(node, Tree_new_Node('1'));
            break;
        case 15:
            Stack_push(stack, "2");
            Tree_set_LMC(node, Tree_new_Node('2'));
            break;
        case 16:
            Stack_push(stack, "3");
            Tree_set_LMC(node, Tree_new_Node('3'));
            break;
        case 17:
            Stack_push(stack, "4");
            Tree_set_LMC(node, Tree_new_Node('4'));
            break;
        case 18:
            Stack_push(stack, "5");
            Tree_set_LMC(node, Tree_new_Node('5'));
            break;
        case 19:
            Stack_push(stack, "6");
            Tree_set_LMC(node, Tree_new_Node('6'));
            break;
        case 20:
            Stack_push(stack, "7");
            Tree_set_LMC(node, Tree_new_Node('7'));
            break;
        case 21:
            Stack_push(stack, "8");
            Tree_set_LMC(node, Tree_new_Node('8'));
            break;
        case 22:
            Stack_push(stack, "9");
            Tree_set_LMC(node, Tree_new_Node('9'));
            break;
        default:
            return;

    }
}


void TDP_addProduction(char *c) {

    int production = paseTable[s_to_int(*c)][i_to_int(*nextInputChar)];


    if(i_to_int(*nextInputChar)==-1){
        production = 1;
    }

    if(i_to_int(*nextInputChar)==100)
        production = -1;

    TDP_Find_Production(production);

}


pNODE TDP_Parse(char *input) {

    nextInputChar = input;
    stack = Stack_new();
    Stack_push(stack, "E");
    root = Tree_new_Node('E');


    while (!Stack_is_empty(stack)) {


        char *tp = Stack_pop(stack);

        if (TDP_isTerminal(*tp)) {
            TDP_MatchTerminal(*tp);
        } else {
            TDP_addProduction(tp);
        }


    }

    Stack_free(stack);

    if(!(*nextInputChar == '\n'))
        return NULL;

    if(root==NULL) {
        return NULL;
    }

    return root;
}



