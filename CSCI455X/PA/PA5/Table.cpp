// Name:Chengyu Lu
// USC NetID:luchengy
// CSCI 455 PA5
// Spring 2023

// Table.cpp  Table class implementation


#include "Table.h"

#include <iostream>
#include <string>
#include <cassert>

// for hash function called in private hashCode method defined below
#include <functional>

using namespace std;


// listFuncs.h has the definition of Node and its methods.  -- when
// you complete it it will also have the function prototypes for your
// list functions.  With this #include, you can use Node type (and
// Node*, and ListType), and call those list functions from inside
// your Table methods, below.

#include "listFuncs.h"


//*************************************************************************

/*
   Table constructor without variable
*/
Table::Table() {
   hashSize = HASH_SIZE;
   table = new ListType[hashSize]();
}

/*
   Table constructor with variable
*/
Table::Table(unsigned int hSize) {
   hashSize = hSize;
   table = new ListType[hashSize]();
}

/*
   lookup the key and value in the tablee
*/
int * Table::lookup(const string &key) {
   int bucket = hashCode(key);
   ListType list = table[bucket];
   while(list != NULL) {
      if(list->key == key) {
         return &list->value;
      }
      list = list->next;
   }
   return NULL;   // dummy return value for stub
}

/*
   remove the key and value in the table
*/
bool Table::remove(const string &key) {
   int bucket = hashCode(key);
   return listRemove(table[bucket],key);  // dummy return value for stub
}

/*
   insert the key and value in the table
*/
bool Table::insert(const string &key, int value) {
   int bucket = hashCode(key);
   bool temp = listAdd(table[bucket], key, value);
   return temp;  // dummy return value for stub
}

/*
   return the number of entries
*/
int Table::numEntries() const {
   int numEntries = 0;
   for(int i = 0; i < hashSize; ++i){
      numEntries += listSize(table[i]);
   }
   return numEntries;      // dummy return value for stub
}

/*
   print all in the table
*/
void Table::printAll() const {
   for(int i = 0; i < hashSize; ++i){
      ListType list = table[i];
      if(list != NULL){
         listPrint(list);
      }
   }
}

/*
   print the stats
*/
void Table::hashStats(ostream &out) const {
   out << "number of buckets: " << hashSize << endl;
   out << "number of entries: " << numEntries() << endl;
   out << "number of non-empty buckets: " << numNonEmpty() << endl;
   out << "longest chain: " << longestChain() << endl;
}


// hash function for a string
// (we defined it for you)
// returns a value in the range [0, hashSize)
unsigned int Table::hashCode(const string &word) const {

   // Note: calls a std library hash function for string (it uses the good hash
   //   algorithm for strings that we discussed in lecture).
   return hash<string>()(word) % hashSize;

}


// add definitions for your private methods here

/*
   find the longest chain
*/
int Table::longestChain()const{
   int longestChain = 0;
   for(int i = 0; i < hashSize; ++i){
      if(longestChain < listSize(table[i])){
         longestChain = listSize(table[i]);
      }
   }
   return longestChain;
}

/*
   find the number of non-empty buckets
*/
int Table::numNonEmpty()const{
   int num = 0;
   for(int i = 0; i < hashSize; ++i){
      if(0 < listSize(table[i])){
         ++num;
      }
   }
   return num;
}