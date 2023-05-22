// Name:Chengyu Lu
// USC NetID:luchengy
// CSCI 455 PA5
// Spring 2023


//*************************************************************************
// Node class definition 
// and declarations for functions on ListType

// Note: we don't need Node in Table.h
// because it's used by the Table class; not by any Table client code.

// Note2: it's good practice to *not* put "using" statement in *header* files.  Thus
// here, things from std libary appear as, for example, std::string

#ifndef LIST_FUNCS_H
#define LIST_FUNCS_H

#include <string>
  
using namespace std;

struct Node {
   std::string key;
   int value;

   Node *next;

   Node(const std::string &theKey, int theValue);

   Node(const std::string &theKey, int theValue, Node *n);
};


typedef Node * ListType;

//*************************************************************************
//add function headers (aka, function prototypes) for your functions
//that operate on a list here (i.e., each includes a parameter of type
//ListType or ListType&).  No function definitions go in this file.

/*
   Remove the target in the list
*/
bool listRemove(ListType & list, const string & target);

/*
   if list contain target return true else false
*/
bool listContain(ListType &list, const string & target);

/*
   return the list size
*/
int listSize(ListType &list);

/*
   Add theKey and theValue in the list
*/
bool listAdd(ListType &list, const string & theKey, int theValue);

/*
   print all in the list
*/
void listPrint(ListType &list);

/*
   update theKey in the list with theValue
*/
bool listUpdate(ListType &list, const string & theKey, int theValue);

// keep the following line at the end of the file
#endif
