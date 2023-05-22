// Name: Chengyu Lu
// USC NetID: luchengy
// CS 455 PA4
// Spring 2023

import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.HashMap;
import java.util.Arrays;
import java.io.File;


/**
   A dictionary of all anagram sets. 
   Note: the processing is case-sensitive; so if the dictionary has all lower
   case words, you will likely want any string you test to have all lower case
   letters too, and likewise if the dictionary words are all upper case.
 */
public class AnagramDictionary {
   
    /**
     * Representation invariants:
     * 1. The anagramDictionary stores the anagrams in the dictionary, it should not be null
     */
   private HashMap<String, ArrayList<String>> anagramDictionary;


   /**
      Create an anagram dictionary from the list of words given in the file
      indicated by fileName.  
      @param fileName  the name of the file to read from
      @throws FileNotFoundException  if the file is not found
      @throws IllegalDictionaryException  if the dictionary has any duplicate words
    */
   public AnagramDictionary(String fileName) throws FileNotFoundException,IllegalDictionaryException {
      anagramDictionary = new HashMap<String, ArrayList<String>>();
      File file = new File(fileName);
      Scanner in = new Scanner(file);
      while(in.hasNext()){
         String word = in.next();
         char[] chars = word.toCharArray();
         Arrays.sort(chars);
         String sortedWord = new String(chars);
         if (anagramDictionary.containsKey(sortedWord)) {
            if(anagramDictionary.get(sortedWord).contains(word)){
               throw new IllegalDictionaryException(word);
            }
            anagramDictionary.get(sortedWord).add(word);
         }
         else{
            ArrayList<String> temp = new ArrayList<String>();
            temp.add(word);
            anagramDictionary.put(sortedWord, temp);
         }
      }
      assert isValidAnagramDictionary();
   }
   

   /**
      Get all anagrams of the given string. This method is case-sensitive.
      E.g. "CARE" and "race" would not be recognized as anagrams.
      @param s string to process
      @return a list of the anagrams of s
    */
   public ArrayList<String> getAnagramsOf(String string) {
      char[] chars = string.toCharArray();
      Arrays.sort(chars);
      String sortedWord = new String(chars);
      if(!anagramDictionary.containsKey(sortedWord)){
         return new ArrayList<String>();
      }
      else{
         return anagramDictionary.get(sortedWord);
      }
   }
   
   /**
    Check whether the ValidAnagramDictionary is valid or not
    If ValidAnagramDictionary is valid, return true, otherwise, return false
    */
   public  boolean isValidAnagramDictionary(){
      if(anagramDictionary == null){
         return false;
      }
      else{
         return true;
      }
   }
}
