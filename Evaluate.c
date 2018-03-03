#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "Tree.h"
#include "RDP.h"
#include "Evaluate.h"

//bool Use_Result ;

int char_to_int(char c) {
    return (int) c - 48;
}

double evaluate_Tree(pNODE root) {



    if (Tree_get_data(root) == 'E') {

        return evaluate_Tree(Tree_get_LMC(root));
    }
    if (Tree_get_data(root) == 'T') {

        return evaluate_T(root, 0);
    }
    if (Tree_get_data(root) == 'F') {
        return evaluate_F(root, 0);


    }
    if (Tree_get_data(root) == 'N') {
        return evaluate_N(root);
    }

    return 0;

}

double evaluate_N(pNODE root) {
    pNODE tp = Tree_get_LMC(Tree_get_RS(Tree_get_LMC(root)));
    pNODE root_tp = root;
    double num = (double) char_to_int(Tree_get_data(Tree_get_LMC(Tree_get_LMC(root_tp))));
    while (!(Tree_get_data(tp) == 'e')) {
        num = num * 10 + (double) char_to_int(Tree_get_data(Tree_get_LMC(Tree_get_LMC(tp))));
        root_tp = tp;
        tp = Tree_get_LMC(Tree_get_RS(Tree_get_LMC(tp)));
    }
    return num;
}

double evaluate_F(pNODE root, double result) {
    pNODE tp = Tree_get_LMC(Tree_get_RS(root));
    if (Tree_get_data(Tree_get_parent(root)) == 'T') {

        if (Tree_get_data(Tree_get_LMC(root)) == '(') {
            result = evaluate_Tree(Tree_get_RS(Tree_get_LMC(root)));

        } else
            result = evaluate_N(Tree_get_LMC(root));


        if (Tree_get_data(tp) == 'e') {
            return result;
        }

        return evaluate_F(Tree_get_RS(Tree_get_LMC(Tree_get_RS(root))), result);

    } else if (Tree_get_data(Tree_get_parent(root)) == 'f') {

        if (Tree_get_data(Tree_get_LMC(Tree_get_parent(root))) == '*') {

            if (Tree_get_data(Tree_get_LMC(root)) == '(') {
                result = result * evaluate_Tree(Tree_get_RS(Tree_get_LMC(root)));

            } else {
                result = result *
                         evaluate_N(Tree_get_LMC(root));
            }

            if (Tree_get_data(tp) == 'e') {
                return result;
            }

            return evaluate_F(Tree_get_RS(Tree_get_LMC(Tree_get_RS(root))), result);
        }
        if (Tree_get_data(Tree_get_LMC(Tree_get_parent(root))) == '/') {
            if (Tree_get_data(Tree_get_LMC(root)) == '(') {
                result = result / evaluate_Tree(Tree_get_RS(Tree_get_LMC(root)));

            } else {
                result = result /
                         evaluate_N(Tree_get_LMC(root));
            }
            if (Tree_get_data(tp) == 'e') {
                return result;
            }

            return evaluate_F(Tree_get_RS(Tree_get_LMC(Tree_get_RS(root))), result);
        }
    }


    return 0;
}

double evaluate_T(pNODE root, double result) {
    //printf("rrrresult= %f",result);

    pNODE tp = Tree_get_LMC(Tree_get_RS(root));

    if (Tree_get_data(Tree_get_parent(root)) == 'E') {

        result = evaluate_F(Tree_get_LMC(root), result);

        if (Tree_get_data(tp) == 'e') {
            return result;
        }

        return evaluate_T(Tree_get_RS(Tree_get_LMC(Tree_get_RS(root))), result);

    } else if (Tree_get_data(Tree_get_parent(root)) == 't') {

        if (Tree_get_data(Tree_get_LMC(Tree_get_parent(root))) == '+') {
            result = result +
                     evaluate_F(Tree_get_LMC(root), result);

            if (Tree_get_data(tp) == 'e') {
                return result;
            }
            return evaluate_T(Tree_get_RS(Tree_get_LMC(Tree_get_RS(root))), result);
        }
        if (Tree_get_data(Tree_get_LMC(Tree_get_parent(root))) == '-') {
            result = result -
                     evaluate_F(Tree_get_LMC(root), result);
            if (Tree_get_data(tp) == 'e') {
                return result;
            }

            return evaluate_T(Tree_get_RS(Tree_get_LMC(Tree_get_RS(root))), result);
        }
    }

    return 0;

}