// Name:Chengyu Lu
// USC NetID:luchengy
// CSCI 455 PA5
// Spring 2023

/*
 * grades.cpp
 * A program to test the Table class.
 * How to run it:
 *      grades [hashSize]
 * 
 * the optional argument hashSize is the size of hash table to use.
 * if it's not given, the program uses default size (Table::HASH_SIZE)
 *
 */

#include "Table.h"

// cstdlib needed for call to atoi
#include <cstdlib>

using namespace std;

/*
   Insert this name and score in the grade table. If this name was already present, print a message to that effect, and don't do the insert.
*/
static void insertStudent(Table* table){
   int score;
   string name;
   cin >> name >> score;
   if(!table->insert(name, score)){
      cout << name << " was already present, don't do the insert." << endl;
   }
}

/*
   Change the score for name. Print an appropriate message if this name isn't present.
*/
static void changeScore(Table* table){
   int score;
   string name;
   cin >> name >> score;
   int* Score = table->lookup(name);
   if(Score == NULL){
      cout << name << " isn't present, don't do the change." << endl;
   }
   else{
      *Score = score;
   }
}

/*
   Lookup the name, and print out his or her score, or a message indicating that student is not in the table.
*/
static void lookupStudent(Table* table){
   string name;
   cin >> name;
   int* Score = table->lookup(name);
   if(Score == NULL){
      cout << name << " is not in the table." << endl;
   }
   else{
      cout << name << ": " << *Score << endl;
   }
}

/*
   Remove this student. If this student wasn't in the grade table, print a message to that effect.
*/
static void removeStudent(Table* table){
   string name;
   cin >> name;
   if(!table->remove(name)){
      cout << name << " wasn't in the grade table." << endl;
   }
}

/*
   Prints out a brief command summary.
*/
static void help(){
   cout << "insert name score" << endl;
   cout << "Insert this name and score in the grade table. If this name was already present, print a message to that effect, and don't do the insert." << endl<< endl;
   cout << "change name newscore" << endl;
   cout << "Change the score for name. Print an appropriate message if this name isn't present." << endl<< endl;
   cout << "lookup name" << endl;
   cout << "Lookup the name, and print out his or her score, or a message indicating that student is not in the table." << endl<< endl;
   cout << "remove name" << endl;
   cout << "Remove this student. If this student wasn't in the grade table, print a message to that effect." << endl<< endl;
   cout << "print" << endl;
   cout << "Prints out all names and scores in the table." << endl<< endl;
   cout << "size" << endl;
   cout << "Prints out the number of entries in the table." << endl<< endl;
   cout << "stats" << endl;
   cout << "Prints out statistics about the hash table at this point. (Calls hashStats() method)" << endl;
   cout << "help" << endl;
   cout << "Prints out a brief command summary." << endl<< endl;
   cout << "quit" << endl;
   cout << "Exits the program." << endl;
}

/*
   Deal with input cmd.
*/
static void menu(Table* table){
   while(true){
      cout << "cmd> ";
      string cmd;
      cin >> cmd;      
      if(cmd == "insert"){
         insertStudent(table);
      }
      else if(cmd == "change"){
         changeScore(table);
      }
      else if(cmd == "lookup"){
         lookupStudent(table);
      }
      else if(cmd == "remove"){
         removeStudent(table);
      }
      else if(cmd == "print"){
         table->printAll();
      }
      else if(cmd == "size"){
         cout << "Number of entries in the table: " << table->numEntries() << endl;
      }
      else if(cmd == "stats"){
         table->hashStats(cout);
      }
      else if(cmd == "help"){
         help();
      }
      else if(cmd == "quit"){
         break;
      }
      else{
         cout << "ERROR: invalid command." << endl;
         help();
      }
   }
}

int main(int argc, char * argv[]) {


   Table * grades;  // Table is dynamically allocated below, so we can call
                     // different constructors depending on input from the user.
   
   // optionally gets the hash table size from the command line
   if (argc > 1) {
      int hashSize = atoi(argv[1]);  // atoi converts c-string to int
      
      if (hashSize < 1) {
         cout << "Command line argument (hashSize) must be a positive number" 
              << endl;
         return 1;
      }

      grades = new Table(hashSize);

   }
   else {   // no command line args given -- use default table size
      grades = new Table();
   }


   grades->hashStats(cout);

   // add more code here
   // Reminder: use -> when calling Table methods, since grades is type Table*
   menu(grades);

   return 0;
}
