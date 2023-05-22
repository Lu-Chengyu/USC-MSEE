// Name: Chengyu Lu
// USC NetID: luchengy
// CS 455 PA4
// Spring 2023

/**
   Class ScoreTable has information about how much each scrabble letter is worth.
 */
public class ScoreTable {
   
    /**
     * Representation invariants:
     * 1. The SCORES store the scores for each letter from A to Z and it is constant
     */

   // The following are the scores of 26 different letters:
   public static final int[] SCORES = { 
      1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 
   };

   /**
    Calculate the score of a word according to SCORES of letters. 
    @param word the given word
    @Return sumScore: the total score after calculating
   */
   public static int sumScore(String word) {
      int sumScore = 0;
      for(int i = 0; i < word.length(); ++i) {
         int score = 0;
         if(word.charAt(i) <= 'Z' && word.charAt(i) >= 'A') {
            score = SCORES[word.charAt(i) - 'A'];
         }         
         else if(word.charAt(i) <= 'z' && word.charAt(i) >= 'a') {
            score = SCORES[word.charAt(i) - 'a'];
         }
         sumScore += score;
      }
      return sumScore;
   }
   
}