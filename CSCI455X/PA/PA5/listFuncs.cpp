// Name:Chengyu Lu
// USC NetID:luchengy
// CSCI 455 PA5
// Spring 2023


#include <iostream>

#include <cassert>

#include "listFuncs.h"

using namespace std;

Node::Node(const string &theKey, int theValue) {
   key = theKey;
   value = theValue;
   next = NULL;
}

Node::Node(const string &theKey, int theValue, Node *n) {
   key = theKey;
   value = theValue;
   next = n;
}




//*************************************************************************
// put the function definitions for your list functions below

/*
   Remove the target in the list
*/
bool listRemove(ListType & list, const string & target) {
   ListType pointer = list;
   ListType frontPointer = NULL;
   while (pointer != NULL)
   {
      if (pointer->key == target)
      {
         if (frontPointer == NULL)
         {
            list = pointer->next;
            delete pointer;
         }
         else
         {
            frontPointer->next = pointer->next;
            delete pointer;
         }
         return true;
      }
      frontPointer = pointer;
      pointer = pointer->next;
   }
   return false;
}

/*
   if list contain target return true else false
*/
bool listContain(ListType &list, const string & target){
   ListType pointer = list;

   while (pointer != NULL)
   {
      if (pointer->key == target)
      {
         return true;
      }
      pointer = pointer->next;
   }
   return false;
}

/*
   return the list size
*/
int listSize(ListType &list){
   int listSize = 0;
   ListType pointer = list;
   while (pointer != NULL)
   {
      listSize++;
      pointer = pointer->next;
   }
   return listSize;
}

/*
   Add theKey and theValue in the list
*/
bool listAdd(ListType &list, const string & theKey, int theValue){
   if (listContain(list, theKey) == true)
   {
      return false;
   }
   else
   {
      list = new Node(theKey, theValue, list);
      return true;
   }
}

/*
   print all in the list
*/
void listPrint(ListType &list){
   if (list == NULL)
   {
      cout << "List is empty." << endl;
   }
   ListType pointer = list;
   while (pointer != NULL)
   {
      cout << pointer->key << " " << pointer->value << endl;
      pointer = pointer->next;
   }
}

/*
   update theKey in the list with theValue
*/
bool listUpdate(ListType &list, const string & theKey, int theValue){
   ListType pointer = list;
   while (pointer != NULL)
   {
      if (pointer->key == theKey)
      {
         pointer->value = theValue;
         return true;
      }
      pointer = pointer->next;
   }
   return false;
}
