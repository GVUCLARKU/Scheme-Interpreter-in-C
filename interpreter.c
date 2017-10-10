/****************************************************************
 File: interpreter.c
 Author: Giang Vu
 Course: CS170
 Date: 3/23/2017
 -------------
 This file is main method to run project in cmd and print desired
 output given the user input.
 ***************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "list.h"
#include "list_func.h"

int main() {
    printf("\nA prototype evaluator for Scheme.\n");
    printf("Type Scheme expressions using quote,\n");
    printf("car, cdr, cons and symbol?.\n");
    printf("The function call (exit) quits.\n");
    while(1) {
        printf("\nscheme> ");
        List expr = S_Expression();
        printList(eval(expr));
	printf("\n");
    }
}
