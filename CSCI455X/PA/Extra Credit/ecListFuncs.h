// ecListFuncs.h
// CSCI 455 Spring 2023, Extra Credit assignment
// You do not need to modify or submit this file.

#ifndef EC_LIST_FUNCS_H
#define EC_LIST_FUNCS_H

#include <iostream>
#include <string>


//*************************************************************************
// Node type used for lists
struct Node {
   int data;
   Node *next;

   Node(int item);
   Node(int item, Node *n);

};


typedef Node * ListType;


//*************************************************************************
// Functions you need to write for this assignment:
//   (implementations go in ecListFuncs.cpp)



/*
 * allUnique
 *
 * PRE: list is a well-formed list.
 *
 * returns true iff all the values in the list are unique (i.e., there are no duplicate
 * values int hte linked list).
 *
 * RESTRICTION on solution: your solution must only use a constant amount of extra memory, and
 * of course, should not modify the list.
 *
 * Examples:
 *  list:               allUnique(list)
 *    (3 4 -5)          true
 *    (6 7 3 6 4 5)     false
 *    (3 3)             false
 *    ()                true
 *    (5)               true
 */
bool allUnique(ListType list);


/*
 * merge
 *
 * PRE: list1 and list 2 are each well-formed lists with values in non-decreasing (sorted) order.
 *
 * returns a well-formed list of all the values from list1 and list2
 * in non-decreasing (sorted) order.  This is a destructive merge, i.e,
 * it will reuse the nodes from the original lists, so it's not safe to 
 * use list1 or list2 after returning from this function,
 *
 * RESTRICTION on solution: this function must operate in worst case O(m + n)
 * time, where m and n are the lengths of the two original lists.
 *
 * Examples:
 *   list1:              list2:               return value of merge(list1, list2)
 *    (1 3 5)            (2 4 6)              (1 2 3 4 5 6)
 *    (2 3 6)            (1 3 5)              (1 2 3 3 5 6)
 *    (1 3 3 3 5)        (2 6)                (1 2 3 3 3 5 6)
 *    ()                 (1 3)                (1 3)
 *    (1 3)              ()                   (1 3)
 *    ()                 ()                   ()
 */
ListType merge(ListType list1, ListType list2);


/*
 * triSum
 *
 * PRE: list is a well-formed list.
 *
 * triSum replaces the first three values with their sum, the second
 * three values with their sum, etc., until it reaches the end of the
 * list.  If the number of elements in the original list is not a
 * multiple of three, just adds the leftover values together for the
 * last node of the modified list (see examples below).
 * 
 * Examples:
 *  list:                   list  after call to triSum(list)
 *    (3 4 -5)              (2)
 *    (6 7 6 3 4 5)         (19 12)
 *    (3 7)                 (10)
 *    ()                    ()
 *    (5)                   (5)
 *    (0 1 2 3 4 5 6 7)     (3 12 13)
 *    (0 1 2 3 4 5 6)       (3 12 6)
 */
void triSum(ListType & list);

//*************************************************************************

#endif
