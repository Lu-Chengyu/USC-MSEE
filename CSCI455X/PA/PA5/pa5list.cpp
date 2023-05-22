// Name:Chengyu Lu
// USC NetID:luchengy
// CSCI 455 PA5
// Spring 2023

// pa5list.cpp
// a program to test the linked list code necessary for a hash table chain

// You are not required to submit this program for pa5.

// We gave you this starter file for it so you don't have to figure
// out the #include stuff.  The code that's being tested will be in
// listFuncs.cpp, which uses the header file listFuncs.h

// The pa5 Makefile includes a rule that compiles these two modules
// into one executable.

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

#include "listFuncs.h"

void add(ListType &list, string name, int value)
{
   if (listAdd(list, name, value)){
      cout << "Add successfully" << endl;
      listPrint(list);
   }
   else{
      cout << "add fails" << endl;
   }
}

void remove(ListType &list, string name){
   if (listRemove(list, name)){
      cout << "Remove successfully" << endl;
      listPrint(list);
   }
   else{
      cout << "remove fails" << endl;
   }
}

void update(ListType &list, string name, int newValue){
   if (listUpdate(list, name, newValue)){
      cout << "update successfully" << endl;
      listPrint(list);
   }
   else{
      cout << "update fails" << endl;
   }
}

void contain(ListType &list, string name){
   if (listContain(list, name)){
      cout << "YES it contains " << name << endl;

   }
   else{
      cout << "NO it does not cotain " << name << endl;
   }
}

void size(ListType &list){
      cout << "list has " << listSize(list) <<" nodes"<< endl;
}

int main() {
   ListType list = NULL;
   int score;
   string name;   
   char command;
   bool handle = true;
   while (handle){
      cout << "(a)Add, (c)Contain, (n)Number, (r)Remove, (u)Update, (q)Quit: ";
      cin >> command;
      switch (command){
      case 'a':
         cout << "name: ";
         cin >> name;
         cout << "score: ";
         cin >> score;
         add(list, name, score);
         break;
      case 'c':
         cout << "name: ";
         cin >> name;
         contain(list, name);
         break;
      case 'n':
         size(list);
         break;
      case 'r':
         cout << "name: ";
         cin >> name;
         remove(list, name);
         break;
      case 'u':
         cout << "name: ";
         cin >> name;
         cout << "score: ";
         cin >> score;
         update(list, name, score);
         break;
      case 'q':
         handle = false;
         break;
      default:
         cout << endl;
         break;
      }
   }
   return 0;
}
