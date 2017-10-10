/****************************************************************
 File: list_func.c
 Author: Giang Vu
 Course: CS170
 Date: 3/23/2017
 ----------------
 Implement List function - eval, quote, cons,car, cdr, exit.
 Include new functions: append, cond, assoc,define.
 Include some other user defined function and math.
 ***************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "parser.h"
#include "list_func.h"

/****************************************************************
 Static Function Declarations
 ----------------------------
 Declaring functions for later use.
 ****************************************************************/
// containing user defined vars
static List environment;

// control functions
static int initialized = 0;
static void initialize();
static List userDefinedFunction(List list, List environment);
static List Environment(List User, List params, List environment);
static List createPair(List key, List value);
static int insideIsSymbol(List list);
static void exitInterpreter();

// Helps with multivariable functions
static List evalHelper(List list, List environment);
static List consHelper(List list, List environment);
static List appendHelper(List list, List environment);
static List isEqualHelper(List list, List environment);
static List assocHelper(List list, List environment);
static List defineSymbol(List key, List definition);

/****************************************************************
 Functions used to evaluate both user-defined and standard
 functions.
 ****************************************************************/
/**
 * Function: initialize()
 * ------------------------------------
 * Initializes the environment of the current session.
 */
static void initialize() {
    environment = FALSE_LIST;
    initialized = 1;
}

/**
 * Function: eval(List list)
 * ------------------------------------
 * Evaluates an expression.
 */
List eval(List list) {
    if (!initialized) initialize();
    return evalHelper(list, environment);
}



/**
 * Function: evalHelper(List list, List localEnv)
 * ---------------------------------------------------
 * Evaluates an expression given an environment.
 */
static List evalHelper(List list, List localEnv) {
    List local = list;

    if (list == TRUE_LIST) return TRUE_LIST;
    else if (list == FALSE_LIST) return FALSE_LIST;
    else if (insideIsSymbol(list)) return car(cdr(assoc(list, localEnv)));

    // get order of function
    char * order = getSymbol(car(list));

    // special exit function, two param functions, and recursion
    if (strcmp(order, "exit") == 0) exitInterpreter();
    else if (strcmp(order, "cons") == 0) return consHelper(list, localEnv);
    else if (strcmp(order, "append") == 0) return appendHelper(list, localEnv);
    else if (strcmp(order, "equal?") == 0) return isEqualHelper(list, localEnv);
    else if (strcmp(order, "assoc") == 0) return assocHelper(list, localEnv);
    else if (strcmp(order, "define") == 0) return define(list, localEnv);
    else if (strcmp(order, "cond") == 0) return cond(cdr(list), localEnv);
    else if (strcmp(order, "environment") == 0) return environment;
    else if (strcmp(order, "quote") != 0) local = evalHelper(quote(list), localEnv);

    // single param functions and function look up
    if (strcmp(order, "quote") == 0) return quote(local);
    else if (strcmp(order, "car") == 0) return car(local);
    else if (strcmp(order, "cdr") == 0) return cdr(local);
    else if (strcmp(order, "null?") == 0) return isNull(local);
    else if (strcmp(order, "list?") == 0) return isList(local);
    else if (strcmp(order, "symbol?") == 0) return isSymbol(local);
    else return userDefinedFunction(list, localEnv);
}

/**
 * Function: Environment(List User, List params, List environment)
 * ----------------------------------------------------------
 * Augments a given environment with new variables for user
 * defined functions.
 */
static List Environment(List User, List params, List environment) {
    List Pairs = FALSE_LIST;
    List augmented = FALSE_LIST;
    // binds parameters to names
    while (User == TRUE_LIST) {
        List key = car(params);
        List value = evalHelper(car(User), environment);
        List pair = createPair(key, value);
        if (Pairs == FALSE_LIST) Pairs = cons(pair, NULL);
        else Pairs = cons(pair, Pairs);
        params = cdr(params);
        User = cdr(User);
    }
    // adds to new environment
    while (Pairs == TRUE_LIST) {
        if (augmented == FALSE_LIST) augmented = cons(car(Pairs), environment);
        else augmented = cons(car(Pairs), augmented);
        Pairs = cdr(Pairs);
    }
    return augmented;
}

/**
 * Function: userDefinedFunction(List list, List localEnv)
 * ----------------------------------------------------------
 * Evaluates a new user defined function given a list and
 * an local environment.
 */
static List userDefinedFunction(List list, List environment) {
    List pair = assoc(car(list), environment);
    List params = cdr(car(cdr(car(cdr(pair)))));
    List definition = car(cdr(cdr(car(cdr(pair)))));
    List User = cdr(list);
    List augmented = Environment(User, params, environment);
    return evalHelper(definition, augmented);
}

/**
 * Function: assocHelper(List list)
 * ---------------------------------------
 * Helps out the assoc function.
 */
static List assocHelper(List list, List environment) {
    List key = evalHelper(quote(list), environment);
    List reference = evalHelper(quote(cdr(list)), environment);
    return assoc(key, reference);
}

/**
 * Function: assoc(List key, List list)
 * ---------------------------------------
 * Checks a list of key value pairs for a certain key, and returns
 * the pair if it is found. Returns the null list otherwise.
 */
List assoc(List key, List list) {
    if (list == FALSE_LIST) return FALSE_LIST;
    else if (isEqual(key, car(car(list))) == TRUE_LIST) return car(list);
    else return assoc(key, cdr(list));
}

/**
 * Function: defineSymbol(List key, List definition)
 * --------------------------------------------------
 * Defines a new variable on the global environment. 
 */
static List defineSymbol(List key, List definition) {
    List entry = createPair(key, definition);
    if (environment == TRUE_LIST) environment = cons(entry, environment);
    else environment = cons(entry, NULL);
    return key;
}

/**
 * Function: define(List list)
 * ---------------------------------------
 * Defines a new variable on the global environment. 
 */
List define(List list, List environment) {
    List key = car(cdr(list));
    List definition = evalHelper(car(cdr(cdr(list))), environment);

    if (isSymbol(key) == TRUE_LIST) return defineSymbol(key, definition);
    else if (isList(key) == TRUE_LIST) return defineSymbol(car(key), list);
}

/****************************************************************
 Functions used to get data about an expression. This includes
 functions such as quote, car, and cdr.
 ****************************************************************/

/**
 * Function: quote(List list)
 * ------------------------------------
 * Returns the list.
 */
List quote(List list) {
    return car(cdr(list));
}

/**
 * Function: car(List list)
 * ---------------------------------------
 * Returns the first element of the list.
 */
List car(List list) {
    if (getFirst(list) != NULL) return getFirst(list);
    else return FALSE_LIST;
}

/**
 * Function: cdr(List list)
 * ---------------------------------------
 * Returns the rest of the elements of the list.
 */
List cdr(List list) {
    if (getRest(list) != NULL) return getRest(list);
    else return FALSE_LIST;
}

/****************************************************************
 Functions used to construct new lists. Includes cons, append.
 ****************************************************************/
/**
 * Function: appendHelper(List list)
 * ---------------------------------------
 * Helps out with the append function.
 */
static List appendHelper(List list, List env) {
    List list1 = evalHelper(quote(list), env);
    List list2 = evalHelper(quote(cdr(list)), env);
    if (list1 == FALSE_LIST && list2 == FALSE_LIST) return FALSE_LIST;
    else if (list2 == FALSE_LIST) return append(list2, list1);
    else return append(list1, list2);
}

/**
 * Function: append(List list1, List list2)
 * ---------------------------------------
 * Appends one list to another.
 */
List append(List list1, List list2) {
    if (list1 == FALSE_LIST) return list2;
    return cons(car(list1), append((cdr(list1)), list2));
}

/**
 * Function: consHelper(List list)
 * ---------------------------------------
 * Constructs a new list out of two lists. Parses a cons order.
 */
static List consHelper(List list, List env) {
    List list1 = evalHelper(quote(list), env);
    List list2 = evalHelper(quote(cdr(list)), env);
    if (list1 == FALSE_LIST && list2 == FALSE_LIST) return FALSE_LIST;
    else if (list1 == FALSE_LIST) return cons(list2, NULL);
    else if (list2 == FALSE_LIST) return cons(list1, NULL);
    else return cons(list1, list2);
}
/**
 * Function: cons(List list1, List list2)
 * ---------------------------------------
 * Constructs a new list out of two lists.
 */
List cons(List list1, List list2) {
    List newList = createList();
    placeFirst(newList, list1);
    placeRest(newList, list2);
    return newList;
}
/****************************************************************
 Other necessary functions for helping.
 ****************************************************************/
/**
 * Function: insideIsSymbol(List list)
 * ---------------------------------------
 * Checks to see if a symbol is a symbol. Returns a boolean.
 */
int insideIsSymbol(List list) {
    return getSymbol(list) != NULL;
}

/**
 * Function: createPair(List key, List value)
 * ----------------------------------------------------------
 * Given a key and a value, creates a key value pair like below:
      (key value)
 */
static List createPair(List key, List value) {
    List pair = createList();
    placeFirst(pair, key);
    placeRest(pair, createList());
    placeFirst(getRest(pair), value);
    placeRest(getRest(pair), NULL);
    return pair;
}

/**
 * Function: ExitInterpreter()
 * ----------------------------
 * Exits the interpreter.
 */
static void exitInterpreter() {
    printf("Have a nice day!\n\n");
    exit(1);
}

/***************************************************************
 Functions used with booleans and conditionals. Includes methods
 like cond, symbol?, null?, and some others.
 ****************************************************************/

/**
 * Function: cond(List conditional, List env)
 * -------------------------------------------
 * Given a set of conditions, returns the value of the
 * first true condition. Much like a switch statement.
 */
List cond(List conditional, List env) {
    if (conditional == FALSE_LIST) return FALSE_LIST;
    List first = car(conditional);
    List Cond = car(first);
    if (evalHelper(Cond, env) == TRUE_LIST) return evalHelper(car(cdr(first)), env);
    else return cond(cdr(conditional), env);
}

/**
 * Function: isNull(List list)
 * ---------------------------------------
 * Checks to see if a list is the empty list (also false list)
 */
List isNull(List list) {
    if (list == FALSE_LIST) return TRUE_LIST;
    else return FALSE_LIST;
}

/**
 * Function: isSymbol(List list)
 * ---------------------------------------
 * Checks to see if a list is a symbol.
 */
List isSymbol(List list) {
    if (insideIsSymbol(list)) return TRUE_LIST;
    else return FALSE_LIST;
}

/**
 * Function: isList(List list)
 * ---------------------------------------
 * Checks to see if a list is a List.
 */
List isList(List list) {
    if (isSymbol(list) == TRUE_LIST) return FALSE_LIST;
    else return TRUE_LIST;
}

/**
 * Function: isEqualHelper(List list)
 * ---------------------------------------
 * Helps out with the isEqual function.
 */
static List isEqualHelper(List list, List env) {
    List list1 = evalHelper(quote(list), env);
    List list2 = evalHelper(quote(cdr(list)), env);
    return isEqual(list1, list2);
}

/**
 * Function: isEqual(List list1, List list2)
 * ---------------------------------------
 * Checks to see if two lists are equal.
 */
List isEqual(List list1, List list2) {
    if (isSymbol(list1) != isSymbol(list2)) {
        return FALSE_LIST;
    } else if (isSymbol(list1) == TRUE_LIST && isSymbol(list2) == TRUE_LIST) {
        if (strcmp(getSymbol(list1), getSymbol(list2)) != 0) {
            return FALSE_LIST;
        } else {
            return TRUE_LIST;
        }
    }
    if (isEqual(car(list1), car(list2)) == TRUE_LIST &&
            isEqual(cdr(list1), cdr(list2)) == TRUE_LIST) return TRUE_LIST;
    else return FALSE_LIST;
}



