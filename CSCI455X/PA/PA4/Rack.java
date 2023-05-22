// Name: Chengyu Lu
// USC NetID: luchengy
// CS 455 PA4
// Spring 2023


import java.util.Collections;
import java.util.Comparator;
import java.util.ArrayList;
import java.util.Arrays;

/**
   A Rack of Scrabble tiles stores the current rack
 */

public class Rack {
   
    /**
     * Representation invariants:
     * 1. The length of word should be bigger than zero
     */
   
   private String word;
   
   /**
      Create a rack from word 
      @param word the name of the input word
    */
   public Rack(String word) {
      this.word = word;
      assert isValidRack();
   }
   
   /**
    Print number of words found in the dictionary and words sorted in score and alphabetical order.
    @param anagramDictionary the dictoinary
    */
   public void output(AnagramDictionary anagramDictionary) {
      String unique = "";
      int[] mult = new int[word.length()];
      for (int i = 0; i < word.length(); ++i) {
         char letter = word.charAt(i);
         int index = unique.indexOf(letter);
         if (index == -1) {
            mult[unique.length()] = 1;
            unique += letter;
         } else {
            mult[index]++;
         }
      }
      ArrayList<String> words = new ArrayList<String>();
      for (String subset : allSubsets(unique, mult, 0)) {
         char temp[] = subset.toCharArray();
         Arrays.sort(temp);
         String sortedSubset = new String(temp);
         for (String anagram : anagramDictionary.getAnagramsOf(sortedSubset)) {
            words.add(new String(anagram));
         }
      }
      Collections.sort(words, (a, b) -> (ScoreTable.sumScore(b) == ScoreTable.sumScore(a)) ? a.compareTo(b) : (ScoreTable.sumScore(b) - ScoreTable.sumScore(a)));
      System.out.println("We can make " + words.size() + " words from \"" + word + "\"");
      if (words.size() > 0) {
         System.out.println("All of the words with their scores (sorted by score):");
         for (String i : words) {
            System.out.println(ScoreTable.sumScore(i) + ": "+ i);
         }
      }
      assert isValidRack();
   }
   

   /**
      Finds all subsets of the multiset starting at position k in unique and mult.
      unique and mult describe a multiset such that mult[i] is the multiplicity of the char
           unique.charAt(i).
      PRE: mult.length must be at least as big as unique.length()
           0 <= k <= unique.length()
      @param unique a string of unique letters
      @param mult the multiplicity of each letter from unique.  
      @param k the smallest index of unique and mult to consider.
      @return all subsets of the indicated multiset.  Unlike the multiset in the parameters,
      each subset is represented as a String that can have repeated characters in it.
      @author Claire Bono
    */
   private static ArrayList<String> allSubsets(String unique, int[] mult, int k) {
      ArrayList<String> allCombos = new ArrayList<>();
      
      if (k == unique.length()) {  // multiset is empty
         allCombos.add("");
         return allCombos;
      }
      
      // get all subsets of the multiset without the first unique char
      ArrayList<String> restCombos = allSubsets(unique, mult, k+1);
      
      // prepend all possible numbers of the first char (i.e., the one at position k) 
      // to the front of each string in restCombos.  Suppose that char is 'a'...
      
      String firstPart = "";          // in outer loop firstPart takes on the values: "", "a", "aa", ...
      for (int n = 0; n <= mult[k]; n++) {   
         for (int i = 0; i < restCombos.size(); i++) {  // for each of the subsets 
                                                        // we found in the recursive call
            // create and add a new string with n 'a's in front of that subset
            allCombos.add(firstPart + restCombos.get(i));  
         }
         firstPart += unique.charAt(k);  // append another instance of 'a' to the first part
      }
      
      return allCombos;
   }  
   
   
   /**
    Check if the Rack is valid or not
    If valid, return true, otherwise, return false
    */
   private boolean isValidRack() {
      if(word.length() <= 0) {
         return false;
      }
      else{
         return true;
      }
   }
}

