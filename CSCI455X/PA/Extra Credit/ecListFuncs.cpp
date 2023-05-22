/*  Name:Chengyu Lu
 *  USC NetID:luchengy
 *  CS 455 Spring 2023
 *
 *  See ecListFuncs.h for specification of each function.
 */

#include <string>
#include <cassert>

#include "ecListFuncs.h"

using namespace std;

// *********************************************************
// Node constructors: do not change
Node::Node(int item) { 
   data = item;
   next = NULL;
}

Node::Node(int item, Node *n) {
   data = item;
   next = n;
}
// *********************************************************


bool allUnique(ListType list) {
    ListType temp;
    if(list == NULL || list->next == NULL){
       return true;
    }
    while(list != NULL){
        temp = list->next;
        while(temp != NULL){
            if(temp->data == list->data){
                return false;
            }
            temp = temp->next;
        }
        list = list->next;
    }
    return true;
}


ListType merge(ListType list1, ListType list2) {
   ListType resultList = NULL;
   if (list1 == NULL){
      return list2;
   }
   else if (list2 == NULL){
      return list1;
   }
   if (list1->data > list2->data){
      resultList = list2;
      resultList->next = merge(list1, list2->next);
   }
   else if (list1->data < list2->data){
      resultList = list1;
      resultList->next = merge(list1->next, list2);
   }
   else{
      resultList = list1;
      resultList->next = merge(list1->next, list2);
   }
   return resultList;
}


void triSum(ListType & list)
{
   if (list == NULL){
      return;
   }
   ListType current = list;
   ListType prev = NULL;
   int sum = 0;
   int count = 0;
   while (current != NULL) {
      sum += current->data;
      count++;
      if (count % 3 == 0) {
         if (prev == NULL) {
            list->data = sum;
            ListType temp1 = list->next;
            ListType temp2 = temp1->next;
            list->next = current->next;
            delete temp1;
            delete temp2;
         } else {
            prev->next->data = sum;
            ListType temp1 = prev->next->next;
            ListType temp2 = temp1->next;
            prev->next->next = current->next;
            delete temp1;
            delete temp2;
         }
         sum = 0;
         prev = current;
      }
      current = current->next;
   }
   if (count % 3 != 0) {
      if (prev == NULL) {
         list->data = sum;
         list->next = NULL;
      } else {
         prev->next->data = sum;
         prev->next->next = NULL;
      }
   }
}




