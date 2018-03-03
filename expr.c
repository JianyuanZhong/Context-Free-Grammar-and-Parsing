#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Tree.h"
#include "RDP.h"
#include "TDP.h"
#include "Evaluate.h"

int main(int argc, char *argv[]){

    while(true) {
        printf("\nPlease enter your input to calculate(q to quit): \n\n");
        printf("%s", "Enter an input string (up to 64 chars): ");
        char *input = (char *) malloc(65);

        fgets(input, 65, stdin);
        
        if(strlen(input)==2 && *input=='q')
            return 0;

        printf("\nRECURSIVE DESCENT PARSING:\n");

        pNODE root = RDP_new(input);

        if(root == NULL) {
            printf("Input is not Well-Formed!!\n");
        }else {
            Tree_print(root);
            double result =  evaluate_Tree(root);
            if(result == INFINITY)
                printf("ERROR! TRY TO DIVIDE NUMBER BY 0.\n");
            else
                printf("Result: %f\n", result);
        }

        Tree_free(root);
        
        printf( "\nTABLE DRIVEN PARSING:\n");
        //char *input = (char *) malloc(65);



        pNODE root1 = TDP_Parse(input);
        if(root1 == NULL)
            printf("Input is not Well-Formed!!\n");
        else {
            Tree_print(root1);
            double result1 =  evaluate_Tree(root1);
            if(result1 == INFINITY)
                printf("ERROR! TRY TO DIVIDE NUMBER BY 0.\n");
            else
                printf("Result: %f\n", result1);
        }

        Tree_free(root1);


    }

}
