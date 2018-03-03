#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Tree.h"
#include "RDP.h"

char *nextInputChar;
pNODE root;
pNODE curr;

pNODE RDP_new(char *input){

    nextInputChar=input;
    root = E();

    if(root==NULL) {
        return NULL;
    }

    if(!RDP_Match_Terminal('\n'))
        return NULL;

    return root;
}

bool RDP_Look_Ahead(char c){
    return *nextInputChar == c;
}

int RDP_Match_Terminal(char c){
    if( *nextInputChar == c){

        nextInputChar++;
        return true;
    } else
        return false;
}

bool isDigit(char c){
    switch ( c) {
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
            return true;

    }
    return false;
}

pNODE E(){
    pNODE E_Node = Tree_new_Node('E');

    if(*nextInputChar == '\n'){

        Tree_set_LMC(E_Node,Tree_new_Node('e'));

    } else {

        pNODE p1 = T();
        if (p1 == NULL) return NULL;
        pNODE p2 = TT();
        if (p2 == NULL) return NULL;

        Tree_set_LMC(E_Node, p1);
        Tree_set_RS(p1, p2);



    }

    return E_Node;

}

pNODE TT(){
    pNODE TT_Node = Tree_new_Node('t');

    if(!RDP_Look_Ahead('+') && !RDP_Look_Ahead('-')){
        Tree_set_LMC(TT_Node,Tree_new_Node('e'));
    } else{
        char c = *nextInputChar;
        if(!RDP_Match_Terminal('+') && !RDP_Match_Terminal('-')) return NULL;
        pNODE p1 = T();
        if(p1==NULL) return NULL;
        pNODE p2 = TT();
        if(p2 == NULL) return NULL;

        pNODE temp = Tree_new_Node(c);
        Tree_set_LMC(TT_Node,temp);
        Tree_set_RS(temp,p1);
        Tree_set_RS(p1,p2);

    }
    return TT_Node;
}

pNODE T(){
    pNODE T_Node = Tree_new_Node('T');

    pNODE p1 = F();
    if(p1== NULL) return NULL;
    pNODE p2 = FT();
    if(p2==NULL) return NULL;

    Tree_set_LMC(T_Node,p1);
    Tree_set_RS(p1,p2);
    return T_Node;
}

pNODE FT(){
    pNODE FT_Node = Tree_new_Node('f');
    if(!RDP_Look_Ahead('*') && !RDP_Look_Ahead('/')){
        Tree_set_LMC(FT_Node,Tree_new_Node('e'));
    }else{
        char c = *nextInputChar;
        if(!RDP_Match_Terminal('*') && !RDP_Match_Terminal('/')) return NULL;

        pNODE p1 = F();
        if(p1==NULL) return NULL;
        pNODE p2 = FT();
        if (p2==NULL) return NULL;

        pNODE temp = Tree_new_Node(c);
        Tree_set_LMC(FT_Node,temp);
        Tree_set_RS(temp,p1);
        Tree_set_RS(p1,p2);
    }
    return FT_Node;
}

pNODE F(){
    pNODE F_Node= Tree_new_Node('F');

    if(!RDP_Look_Ahead('(')){
        pNODE p1 = N();
        if(p1==NULL) return NULL;
        Tree_set_LMC(F_Node,p1);
    } else{
        if(!RDP_Match_Terminal('(')) return NULL;
        pNODE p1 = E();
        if(p1 == NULL) return  NULL;
        if(!RDP_Match_Terminal(')')) return NULL;
        pNODE temp= Tree_new_Node('(');
        Tree_set_LMC(F_Node,temp);
        Tree_set_RS(temp, p1);
        Tree_set_RS(p1,Tree_new_Node(')'));
    }
    return F_Node;
}

pNODE N(){
    pNODE N_Node = Tree_new_Node('N');

    pNODE p1 = D();
    if(p1 == NULL) return NULL;

    pNODE p2 = NT();
    if(p2 == NULL) return NULL;

    Tree_set_LMC(N_Node,p1);
    Tree_set_RS(p1,p2);

    return N_Node;


}

pNODE NT(){
    pNODE NT_Node = Tree_new_Node('n');
    if(isDigit(*nextInputChar)){

        pNODE p1 = N();
        if(p1 == NULL) return NULL;

        Tree_set_LMC(NT_Node,p1);
    }else{

        Tree_set_LMC(NT_Node,Tree_new_Node('e'));

    }
    return NT_Node;
}

pNODE D(){
    pNODE D_Node = Tree_new_Node('D');
    if(!isDigit(*nextInputChar)){
        return NULL;
    } else{
        pNODE p1 = Tree_new_Node(*nextInputChar);
        Tree_set_LMC(D_Node,p1);
        nextInputChar++;

    }
    return D_Node;
}
