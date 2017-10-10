/****************************************************************
 File: parser.c
 Author: Giang Vu
 Course: CS170
 Date: 05/08/2017
 -------------
 This file implements the interface given in parser.h.
 Replace function printExpression's name to List readExpression
 to avoid confusion for prof Green.
 ***************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.h"
#include "lexer.h"
#include "list.h"

/****************************************************************
 Data members
 ------------
 token: array of characters stored for token.
 ****************************************************************/
static int item = 0;
static char token[20];

/****************************************************************
 Declaring functions for later use.
 ****************************************************************/
static void initialize();
static List endExpression(List c, int depth);
static List readExpression(int depth);

/****************************************************************
 initialize(): Initializes the parser and makes constant lists.
 ***************************************************************/
static void initialize() {
    item = 1;
    FALSE_LIST = createList();
    placeSymbol(FALSE_LIST, "()");
    TRUE_LIST = createList();
    placeSymbol(TRUE_LIST, "#t");
    startTokens(20);
}

/****************************************************************
 Private function that end and returns an expression. If
 there is more, reads in the next token. End the entire expression
 if depth is 0.
 ****************************************************************/
static List endExpression(List c, int depth) {
    if (depth != 0) {
        strcpy(token, getToken());
    }
    return c;
}

/****************************************************************
 Function: readExpression(int depth)
 ------------------------------------
 Private (recursive) helper method to reads input from the
 user and based on the cons-cell List data type created 
 to prints out the parse tree of S expression as requirement. 
 ****************************************************************/
static List readExpression(int depth) {
    List current, temp;

    if (strcmp(token, "(") == 0) {
        current = createList();
        strcpy(token, getToken());
        placeFirst(current, readExpression(depth + 1));
        temp = current;
        while (strcmp(token, ")") != 0) {
            placeRest(temp, createList());
            temp = getRest(temp);
            placeFirst(temp, readExpression(depth + 1));
        }
        placeRest(temp, NULL);
        return endExpression(current, depth);
    } else if (strcmp(token, "#t") == 0 || strcmp(token, "else") == 0) {
        return endExpression(TRUE_LIST, depth);
    } else if (strcmp(token, "#f") == 0 || strcmp(token, "()") == 0) {
        return endExpression(FALSE_LIST, depth);
     } else if (strcmp(token, "'") == 0) {
        current = createList();
        placeFirst(current, createList());
        placeSymbol(getFirst(current), "quote");
        placeRest(current, createList());
        strcpy(token, getToken());
        placeFirst(getRest(current), readExpression(depth));
        placeRest(getRest(current), NULL);
        return current;
    } else {
        current = createList();
        placeSymbol(current, token);
        return endExpression(current, depth);
    }
}

/****************************************************************
 S_Expression(): See parser.h for documentation.
 ***************************************************************/
List S_Expression() {
    if (item == 0) initialize();
    strcpy(token, getToken());
    return readExpression(0);
}
