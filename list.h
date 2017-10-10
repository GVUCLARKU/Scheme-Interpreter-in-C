/**********************************************************************
 File: list.h
 Author: Giang Vu
 Course: CS170
 Date: 05/08/2017
 -------------
 Contains the interface the list structure. The list structure
 is one of the primary building blocks within Scheme. Lists
 can either point at two more lists, or contain a string.
 *********************************************************************/

#ifndef LIST
#define LIST
#include <stdio.h>
#include <stdlib.h>

/**********************************************************************
 *  Data Type: List
 *  ---------------
 *  Declares a list in the following way: List c;
 */
struct conscell;
typedef struct conscell * List;

/**********************************************************************
 *  Function: createList()
 *  ----------------------
 *  Creates a new List and returns it: List c = createList();
 */
List createList();

/**********************************************************************
 *  Functions: placeFirst(List origin, List insert), getFirst(List origin)
 *  ------------------------------------------------------------------
 *  Sets and get the first element of a list.
 */
List getFirst(List origin);
void placeFirst(List origin, List insert);

/**********************************************************************
 *  Functions: placeSymbol(List origin, char * symbol), getSymbol(List origin)
 *  ------------------------------------------------------------------
 *  Sets and get the symbol of a list.
 */
char * getSymbol(List origin);
void placeSymbol(List origin, char * symbol);

/**********************************************************************
 *  Functions: placeRest(List origin, List insert), getRest(List origin)
 *  ------------------------------------------------------------------
 *  Sets and get the rest of the list.
 */
List getRest(List origin);
void placeRest(List origin, List insert);

/**********************************************************************
 Function to to recursive print out the list.
 */
void printSymbol(List list);
static void printRecursive(List list);
void printBrackets(List list);
void printList(List list);

#endif
