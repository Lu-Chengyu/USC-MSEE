/*  Name:Chengyu Lu
 *  USC NetID:luchengy
 *  CS 455 Spring 2023
 *  Extra credit assignment
 *
 *  ectest.cpp
 *
 *  a non-interactive test program to test the functions described in ecListFuncs.h
 *
 *    to run it use the command:   ectest
 *
 *  Note: this uses separate compilation.  You put your list code ecListFuncs.cpp
 *  Code in this file should call those functions.
 */


#include <iostream>
#include <string>

// for istringstream used in buildList (defined below)
#include <sstream>

#include "ecListFuncs.h"

using namespace std;


// You may use the following two utility functions that will make it easier to test
// your list functions on hard-coded list data and compare it to expected output:
// (function definitions for them appear at the bottom of this file)


/*
 * listToString
 *
 * PRE: list is a well-formed list.
 *
 * converts the list to a string form that has the following format shown by example.
 * the list is unchanged by the function.
 *
 *   string format:
 *
 *   "()"        an empty list
 *   "(3)        a list with one element, 3
 *   "(3 4 5)"   a list with multiple elements: 3 followed by 4 followed by 5
 *
 */
string listToString(ListType list);


/*
 * buildList
 * 
 * PRE: listString only contains numbers (valid integer format) and spaces
 *
 * creates and returns a linked list from a string of space separated numbers
 * 
 *
 * Examples:
 *  listString         return value of buildList(listString)
 *
 *    ""               ()
 *    "-32"            (-32)
 *    "     -32   "    (-32)
 *    "1 3 2"          (1 3 2)
 *    "  1 3 2"        (1 3 2)
 *
 */
ListType buildList(const string & listString);




int main (){
   cout << "test allUnique" << endl;
   cout << endl;
    
   cout << "test case 1:" << endl;
   string inputString1 = "3 4 -5";
   ListType inputList1 = buildList(inputString1);
   string expctedallUnique1 = "true";
   string actualallUnique1 = allUnique(inputList1) ? "true" : "false";
   string status1 = expctedallUnique1 == actualallUnique1 ? "SUCCEED" : "FAILED";
   cout << "Input: " + listToString(inputList1) << endl;
   cout << "Expected result: " + expctedallUnique1 << endl;
   cout << "Actual result: " + actualallUnique1 << endl;
   cout << "Status: " + status1 << endl;
   cout<< endl;
    
   cout << "test case 2:" << endl;
   string inputString2 = "6 7 3 6 4 5";
   ListType inputList2 = buildList(inputString2);
   string expctedallUnique2 = "false";
   string actualallUnique2 = allUnique(inputList2) ? "true" : "false";
   string status2 = expctedallUnique2 == actualallUnique2 ? "SUCCEED" : "FAILED";
   cout << "Input: " + listToString(inputList2) << endl;
   cout << "Expected result: " + expctedallUnique2 << endl;
   cout << "Actual result: " + actualallUnique2 << endl;
   cout << "Status: " + status2 << endl;
   cout<< endl;
   
   cout << "test case 3:" << endl;
   string inputString3 = "3 3";
   ListType inputList3 = buildList(inputString3);
   string expctedallUnique3 = "false";
   string actualallUnique3 = allUnique(inputList3) ? "true" : "false";
   string status3 = expctedallUnique3 == actualallUnique3 ? "SUCCEED" : "FAILED";
   cout << "Input: " + listToString(inputList3) << endl;
   cout << "Expected result: " + expctedallUnique3 << endl;
   cout << "Actual result: " + actualallUnique3 << endl;
   cout << "Status: " + status3 << endl;
   cout<< endl;
   
   cout << "test case 4:" << endl;
   string inputString4 = "";
   ListType inputList4 = buildList(inputString4);
   string expctedallUnique4 = "true";
   string actualallUnique4 = allUnique(inputList4) ? "true" : "false";
   string status4 = expctedallUnique4 == actualallUnique4 ? "SUCCEED" : "FAILED";
   cout << "Input: " + listToString(inputList4) << endl;
   cout << "Expected result: " + expctedallUnique4 << endl;
   cout << "Actual result: " + actualallUnique4 << endl;
   cout << "Status: " + status4 << endl;
   cout<< endl;
   
   cout << "test case 5:" << endl;
   string inputString5 = "5";
   ListType inputList5 = buildList(inputString5);
   string expctedallUnique5 = "true";
   string actualallUnique5 = allUnique(inputList5) ? "true" : "false";
   string status5 = expctedallUnique5 == actualallUnique5 ? "SUCCEED" : "FAILED";
   cout << "Input: " + listToString(inputList5) << endl;
   cout << "Expected result: " + expctedallUnique5 << endl;
   cout << "Actual result: " + actualallUnique5 << endl;
   cout << "Status: " + status5 << endl;
   cout<< endl;
   
   cout << "test merge" << endl;
   cout << endl;
   
   cout << "test case 1:" << endl;
   string inputString11 = "1 3 5";
   string inputString12 = "2 4 6";
   ListType inputList11 = buildList(inputString11);
   ListType inputList12 = buildList(inputString12);
   cout << "Input: " + listToString(inputList11) + " " + listToString(inputList12) << endl;
   string expctedmerge1 = "(1 2 3 4 5 6)";
   string actualmerge1 = listToString(merge(inputList11, inputList12));
   string statusMerge1 = expctedmerge1 == actualmerge1 ? "SUCCEED" : "FAILED";
   cout << "Expected result: " + expctedmerge1 << endl;
   cout << "Actual result: " + actualmerge1 << endl;
   cout << "Status: " + statusMerge1 << endl;
   cout<< endl;
   
   cout << "test case 2:" << endl;
   string inputString21 = "2 3 6";
   string inputString22 = "1 3 5";
   ListType inputList21 = buildList(inputString21);
   ListType inputList22 = buildList(inputString22);
   cout << "Input: " + listToString(inputList21) + " " + listToString(inputList22) << endl;
   string expctedmerge2 = "(1 2 3 3 5 6)";
   string actualmerge2 = listToString(merge(inputList21, inputList22));
   string statusMerge2 = expctedmerge2 == actualmerge2 ? "SUCCEED" : "FAILED";
   cout << "Expected result: " + expctedmerge2 << endl;
   cout << "Actual result: " + actualmerge2 << endl;
   cout << "Status: " + statusMerge2 << endl;
   cout<< endl;
   
   cout << "test case 3:" << endl;
   string inputString31 = "1 3 3 3 5";
   string inputString32 = "2 6";
   ListType inputList31 = buildList(inputString31);
   ListType inputList32 = buildList(inputString32);
   cout << "Input: " + listToString(inputList31) + " " + listToString(inputList32) << endl;
   string expctedmerge3 = "(1 2 3 3 3 5 6)";
   string actualmerge3 = listToString(merge(inputList31, inputList32));
   string statusMerge3 = expctedmerge3 == actualmerge3 ? "SUCCEED" : "FAILED";
   cout << "Expected result: " + expctedmerge3 << endl;
   cout << "Actual result: " + actualmerge3 << endl;
   cout << "Status: " + statusMerge3 << endl;
   cout<< endl;
   
   cout << "test case 4:" << endl;
   string inputString41 = "";
   string inputString42 = "1 3";
   ListType inputList41 = buildList(inputString41);
   ListType inputList42 = buildList(inputString42);
   cout << "Input: " + listToString(inputList41) + " " + listToString(inputList42) << endl;
   string expctedmerge4 = "(1 3)";
   string actualmerge4 = listToString(merge(inputList41, inputList42));
   string statusMerge4 = expctedmerge4 == actualmerge4 ? "SUCCEED" : "FAILED";
   cout << "Expected result: " + expctedmerge4 << endl;
   cout << "Actual result: " + actualmerge4 << endl;
   cout << "Status: " + statusMerge4 << endl;
   cout<< endl;
   
   cout << "test case 5:" << endl;
   string inputString51 = "1 3";
   string inputString52 = "";
   ListType inputList51 = buildList(inputString51);
   ListType inputList52 = buildList(inputString52);
   cout << "Input: " + listToString(inputList51) + " " + listToString(inputList52) << endl;
   string expctedmerge5 = "(1 3)";
   string actualmerge5 = listToString(merge(inputList51, inputList52));
   string statusMerge5 = expctedmerge5 == actualmerge5 ? "SUCCEED" : "FAILED";
   cout << "Expected result: " + expctedmerge5 << endl;
   cout << "Actual result: " + actualmerge5 << endl;
   cout << "Status: " + statusMerge5 << endl;
   cout<< endl;
   
   cout << "test case 6:" << endl;
   string inputString61 = "";
   string inputString62 = "";
   ListType inputList61 = buildList(inputString61);
   ListType inputList62 = buildList(inputString62);
   cout << "Input: " + listToString(inputList61) + " " + listToString(inputList62) << endl;
   string expctedmerge6 = "()";
   string actualmerge6 = listToString(merge(inputList61, inputList62));
   string statusMerge6 = expctedmerge6 == actualmerge6 ? "SUCCEED" : "FAILED";
   cout << "Expected result: " + expctedmerge6 << endl;
   cout << "Actual result: " + actualmerge6 << endl;
   cout << "Status: " + statusMerge6 << endl;
   cout<< endl;
   
   cout << "test triSum" << endl;
   cout << endl;
   
   cout << "test case 1:" << endl;
   string triSumInputString1 = "3 4 -5";
   ListType triSumInputList1 = buildList(triSumInputString1);
   cout << "Input: " + listToString(triSumInputList1) << endl;
   string expctedtriSum1 = "(2)";
   triSum(triSumInputList1);
   string actualtriSum1 = listToString(triSumInputList1);
   string statustriSum1 = expctedtriSum1 == actualtriSum1 ? "SUCCEED" : "FAILED";
   cout << "Expected result: " + expctedtriSum1 << endl;
   cout << "Actual result: " + actualtriSum1 << endl;
   cout << "Status: " + statustriSum1 << endl;
   cout<< endl;
   
   cout << "test case 2:" << endl;
   string triSumInputString2 = "6 7 6 3 4 5";
   ListType triSumInputList2 = buildList(triSumInputString2);
   cout << "Input: " + listToString(triSumInputList2) << endl;
   string expctedtriSum2 = "(19 12)";
   triSum(triSumInputList2);
   string actualtriSum2 = listToString(triSumInputList2);
   string statustriSum2 = expctedtriSum2 == actualtriSum2 ? "SUCCEED" : "FAILED";
   cout << "Expected result: " + expctedtriSum2 << endl;
   cout << "Actual result: " + actualtriSum2 << endl;
   cout << "Status: " + statustriSum2 << endl;
   cout<< endl;
   
   cout << "test case 3:" << endl;
   string triSumInputString3 = "3 7";
   ListType triSumInputList3 = buildList(triSumInputString3);
   cout << "Input: " + listToString(triSumInputList3) << endl;
   string expctedtriSum3 = "(10)";
   triSum(triSumInputList3);
   string actualtriSum3 = listToString(triSumInputList3);
   string statustriSum3 = expctedtriSum3 == actualtriSum3 ? "SUCCEED" : "FAILED";
   cout << "Expected result: " + expctedtriSum3 << endl;
   cout << "Actual result: " + actualtriSum3 << endl;
   cout << "Status: " + statustriSum3 << endl;
   cout<< endl;
   
   cout << "test case 4:" << endl;
   string triSumInputString4 = "";
   ListType triSumInputList4 = buildList(triSumInputString4);
   cout << "Input: " + listToString(triSumInputList4) << endl;
   string expctedtriSum4 = "()";
   triSum(triSumInputList4);
   string actualtriSum4 = listToString(triSumInputList4);
   string statustriSum4 = expctedtriSum4 == actualtriSum4 ? "SUCCEED" : "FAILED";
   cout << "Expected result: " + expctedtriSum4 << endl;
   cout << "Actual result: " + actualtriSum4 << endl;
   cout << "Status: " + statustriSum4 << endl;
   cout<< endl;
   
   cout << "test case 5:" << endl;
   string triSumInputString5 = "5";
   ListType triSumInputList5 = buildList(triSumInputString5);
   cout << "Input: " + listToString(triSumInputList5) << endl;
   string expctedtriSum5 = "(5)";
   triSum(triSumInputList5);
   string actualtriSum5 = listToString(triSumInputList5);
   string statustriSum5 = expctedtriSum5 == actualtriSum5 ? "SUCCEED" : "FAILED";
   cout << "Expected result: " + expctedtriSum5 << endl;
   cout << "Actual result: " + actualtriSum5 << endl;
   cout << "Status: " + statustriSum5 << endl;
   cout<< endl;
   
   cout << "test case 6:" << endl;
   string triSumInputString6 = "0 1 2 3 4 5 6 7";
   ListType triSumInputList6 = buildList(triSumInputString6);
   cout << "Input: " + listToString(triSumInputList6) << endl;
   string expctedtriSum6 = "(3 12 13)";
   triSum(triSumInputList6);
   string actualtriSum6 = listToString(triSumInputList6);
   string statustriSum6 = expctedtriSum6 == actualtriSum6 ? "SUCCEED" : "FAILED";
   cout << "Expected result: " + expctedtriSum6 << endl;
   cout << "Actual result: " + actualtriSum6 << endl;
   cout << "Status: " + statustriSum6 << endl;
   cout<< endl;
   
   cout << "test case 7:" << endl;
   string triSumInputString7 = "0 1 2 3 4 5 6";
   ListType triSumInputList7 = buildList(triSumInputString7);
   cout << "Input: " + listToString(triSumInputList7) << endl;
   string expctedtriSum7 = "(3 12 6)";
   triSum(triSumInputList7);
   string actualtriSum7 = listToString(triSumInputList7);
   string statustriSum7 = expctedtriSum7 == actualtriSum7 ? "SUCCEED" : "FAILED";
   cout << "Expected result: " + expctedtriSum7 << endl;
   cout << "Actual result: " + actualtriSum7 << endl;
   cout << "Status: " + statustriSum7 << endl;
   cout<< endl;
   
   return 0;
}



/*********************************************************
 * Utility function definitions
 *
 */
string listToString(ListType list) {

   string listString = "(";

   if (list == NULL) {
      listString += ")";
      return listString;
   }

   Node *p = list;
   while (p->next != NULL) {
      listString += to_string(p->data) + " ";
      p = p->next;
   }

   // print last one with no trailing space
   listString += to_string(p->data) + ")";

   return listString;

}   


ListType buildList(const string & listString) {

   ListType nums = NULL;

   istringstream istr(listString);  // similar to a Java Scanner over a String

   int num;

   if (istr >> num) { // is there one value there?
      nums = new Node(num);
   }
   else {
      return NULL;
   }

   Node *last = nums;

   while (istr >> num) { 
      last->next = new Node(num);
      last = last->next;
   }

   return nums;
}
