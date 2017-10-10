/****************************************************************
 File: list_utils.h
 ------------------
 Commonly used Scheme functions are defined in this file.
 ***************************************************************/

#ifndef LIST_UTILS
#define LIST_UTILS

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/****************************************************************
 Function: eval(List list)
 ----------------------------
 Given a list, evaluates it.
 */
List eval(List list);

/****************************************************************
 Function: assoc(List key, List list)
 ---------------------------------------
 Returns the associated pair given a key.
 */
List assoc(List key, List list);

/****************************************************************
 Function: define(List list)
 ---------------------------------------
 Defines a new variable in the global environment.
 */
List define(List list, List env);

/****************************************************************
 Function: quote(List list)
 ----------------------------
 Given a list, returns it.
 */
List quote(List list);

/****************************************************************
 Function: car(List list)
 ----------------------------
 Given a list, returns the first element.
 */
List car(List list);

/****************************************************************
 Function: cdr(List list)
 ----------------------------
 Given a list, returns everything but the first element.
 */
List cdr(List list);

/****************************************************************
 Function: append(List list1, List list2)
 ---------------------------------------
 Appends one list to another
 */
List append(List list1, List list2);

/****************************************************************
 Function: cons(List list1, List list2)
 ---------------------------------------
 Constructs a new list out of two lists.
 */
List cons(List list1, List list2);

/****************************************************************
 Function: cond(List list)
 ---------------------------------------
 Evaluates a conditional.
 */
List cond(List conditional, List env);


/****************************************************************
 Function: isNull(list)
 ---------------------------------------
 Checks to see if a list is equal to the null list.
 */
List isNull(List list);

/****************************************************************
 Function: isSymbol(List list)
 ---------------------------------------
 Checks to see if a list is a symbol.
 */
List isSymbol(List list);

/****************************************************************
 Function: isList(List list)
 ---------------------------------------
 Checks to see if a list is a list.
 */
List isList(List list);

/****************************************************************
 Function: isEqual(List list1, List list2)
 ---------------------------------------
 Checks to see if tw lists are equal.
 */
List isEqual(List list1, List list2);

#endif