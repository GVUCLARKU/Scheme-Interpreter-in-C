/****************************************************************
 File: list.c
 Author: Giang Vu
 Course: CS170
 Date: 05/08/2017
 -------------
 Implements the interface defined in list.h.
 ****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/****************************************************************
 Data type: List
 ---------------
 Defines the list, which the List data type.
 ***************************************************************/
struct conscell {
    char * symbol; 
    struct conscell * first;
    struct conscell * rest;
};

/****************************************************************
 Creates and returns a new list.
 ***************************************************************/
List createList() {
    List list = (List) malloc(sizeof(List));
    if (list == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }
    list->symbol = NULL;
    list->first = NULL;
    list->rest = NULL;
    return list;
}

/****************************************************************
 Gets the first instance variable of a list.
 ***************************************************************/
List getFirst(List origin) {
    return origin->first;
}
/****************************************************************
 Sets the first instance variable of a origin list.
 ***************************************************************/
void placeFirst(List origin, List insert) {
    origin->first = insert;
}

/****************************************************************
 Gets the symbol instance variable of a list.
 ***************************************************************/
char * getSymbol(List origin) {
    return origin->symbol;
}
/****************************************************************
 Sets the symbol instance variable of a list.
 ***************************************************************/
void placeSymbol(List origin, char * symbol) {
    origin->symbol = (char *) malloc(sizeof(symbol));
    strcpy(origin->symbol, symbol);
}

/****************************************************************
 Gets the rest instance variable of a list.
 ***************************************************************/
List getRest(List origin) {
    return origin->rest;
}
/****************************************************************
 Sets the rest instance variable of a origin list.
 ***************************************************************/
void placeRest(List origin, List insert) {
    origin->rest = insert;
}

/****************************************************************

 Prints out a symbol.
 ****************************************************************/
void printSymbol(List list) {
    printf("%s", getSymbol(list));
}

/****************************************************************
 Private helper method that prints out the content of a list
 ****************************************************************/
static void printRecursive(List list) {
    if (list == NULL) return;
    printList(getFirst(list));
    if (getRest(list) != NULL) printf(" "); 
    printRecursive(getRest(list));
}

/****************************************************************
 Prints out a parenthesized list.
 ****************************************************************/

void printBrackets(List list) {
    printf("("); 
    printRecursive(list);
    printf(")"); 
}

/****************************************************************
 Prints out a list.
 ****************************************************************/
void printList(List list) {
    if (getSymbol(list) != NULL){
        printSymbol(list);
    } else{ 
        printBrackets(list);
    }
}