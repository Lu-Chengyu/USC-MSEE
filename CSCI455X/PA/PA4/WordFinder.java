// Name: Chengyu Lu
// USC NetID: luchengy
// CS 455 PA4
// Spring 2023

import java.util.Scanner;
import java.io.FileNotFoundException;


public class WordFinder {
   public static void main(String[] args) {
      AnagramDictionary anagramDictionary;
      try{
         if (args.length > 0) {
            anagramDictionary = new AnagramDictionary(args[0]);
         }
         else{
            anagramDictionary = new AnagramDictionary("sowpods.txt");
         }
      }
      catch(FileNotFoundException error1) {
         System.out.println("ERROR: Dictionary file \"" + args[0] + "\" does not exist.");
         System.out.println("Exiting program.");
         return;
      }
      catch(IllegalDictionaryException error2) {
         System.out.println("ERROR: Illegal dictionary: dictionary file has a duplicate word: " + error2.getMessage());
         System.out.println("Exiting program.");
         return;
      }
      
      System.out.println("Type . to quit.");
      Scanner in = new Scanner(System.in);
      
      while(true){
         System.out.print("Rack? ");
         String word = in.next();
         if (word.equals(".")) {
            break;
         }
         else{
            Rack rack = new Rack(word);
            rack.output(anagramDictionary);
         }
      }
   }
}