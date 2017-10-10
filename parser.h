/****************************************************************
 File: parser.h
 Author: Giang Vu
 Course: CS170
 Date: 05/08/2017
 ----------------
 The recursive descent parser of Scheme - parser.c 's interface
 Reads a list from input and outputs the parse tree.
 ***************************************************************/
#ifndef PARSER
#define PARSER
#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/****************************************************************
 Two constant lists, representing the true list and false list.
 */
List TRUE_LIST;
List FALSE_LIST;

/****************************************************************
 Function: S_Expression()
 Recursively reads and outputs an S_expression's parse tree.
 For example, if we input: (a (b c))
  => output:   
    S_Expression
    (
      S_Expression
        a
      S_Expression
      (
        S_Expression
          b
        S_Expression
          c
      )
    )
 */
List S_Expression();

#endif