// Name:Chengyu Lu
// USC NetID:luchengy
// CS 455 PA3
// Spring 2023

import java.util.Random;//
/** 
   MineField
      class with locations of mines for a game.
      This class is mutable, because we sometimes need to change it once it's created.
      mutators: populateMineField, resetEmpty
      includes convenience method to tell the number of mines adjacent to a location.
 */
public class MineField {
   
    /**
     * Representation invariants:
     * 1. The size of mineData equals to numRows * numCols
     * 2. numMines equals to the number of trues in mineData
     */
   
   // <put instance variables here>
   private int numRows;//
   private int numCols;
   private int numMines;
   private boolean[][] mineData;//
   
   /**
      Create a minefield with same dimensions as the given array, and populate it with the mines in the array
      such that if mineData[row][col] is true, then hasMine(row,col) will be true and vice versa.  numMines() for
      this minefield will corresponds to the number of 'true' values in mineData.
      @param mineData  the data for the mines; must have at least one row and one col,
                       and must be rectangular (i.e., every row is the same length)
    */
   public MineField(boolean[][] mineData) {
      assert isValidMineData(mineData);//
      numMines = 0;
      numRows = mineData.length;
      numCols = mineData[0].length;
      this.mineData = new boolean[numRows][numCols];
      for(int i = 0; i < numRows; ++i){
         for(int j = 0; j < numCols; ++j){
            this.mineData[i][j] = mineData[i][j];
            if(mineData[i][j]){
               ++ numMines;
            }
         }
      }//
   }
   
   
   /**
      Create an empty minefield (i.e. no mines anywhere), that may later have numMines mines (once 
      populateMineField is called on this object).  Until populateMineField is called on such a MineField, 
      numMines() will not correspond to the number of mines currently in the MineField.
      @param numRows  number of rows this minefield will have, must be positive
      @param numCols  number of columns this minefield will have, must be positive
      @param numMines   number of mines this minefield will have,  once we populate it.
      PRE: numRows > 0 and numCols > 0 and 0 <= numMines < (1/3 of total number of field locations). 
    */
   public MineField(int numRows, int numCols, int numMines) {
      assert numRows > 0 && numCols > 0 && numMines >= 0 && numMines < (numRows * numCols) / 3;
      this.numRows = numRows;//
      this.numCols = numCols;
      this.numMines = numMines;
      mineData = new boolean[numRows][numCols];//
   }
   

   /**
      Removes any current mines on the minefield, and puts numMines() mines in random locations on the minefield,
      ensuring that no mine is placed at (row, col).
      @param row the row of the location to avoid placing a mine
      @param col the column of the location to avoid placing a mine
      PRE: inRange(row, col) and numMines() < (1/3 * numRows() * numCols())
    */
   public void populateMineField(int row, int col) {
      assert inRange(row,col) && numMines() < (numRows() * numCols()) / 3;
      resetEmpty();
      int countMines = 0;
      mineData[row][col] = true;
      Random random = new Random();
      while(countMines < numMines){
         int Row = random.nextInt(numRows);
         int Col = random.nextInt(numCols);
         if(mineData[Row][Col]){
            continue;
         }
         mineData[Row][Col] = true;
         ++ countMines;
      }
      mineData[row][col] = false;
   }
   
   
   /**
      Reset the minefield to all empty squares.  This does not affect numMines(), numRows() or numCols()
      Thus, after this call, the actual number of mines in the minefield does not match numMines().  
      Note: This is the state a minefield created with the three-arg constructor is in 
         at the beginning of a game.
    */
   public void resetEmpty() {
      for(int i = 0; i < numRows; ++i){
         for(int j = 0; j < numCols; ++j){
            mineData[i][j] = false;
         }
      }//
   }

   
  /**
     Returns the number of mines adjacent to the specified mine location (not counting a possible 
     mine at (row, col) itself).
     Diagonals are also considered adjacent, so the return value will be in the range [0,8]
     @param row  row of the location to check
     @param col  column of the location to check
     @return  the number of mines adjacent to the square at (row, col)
     PRE: inRange(row, col)
   */
   public int numAdjacentMines(int row, int col) {
      int num = 0;
      for(int i = -1; i <= 1; ++i){
         for(int j = -1; j <= 1; ++j){
            if(inRange(row+i,col+j) && mineData[row+i][col+j] && !(i==0 && j==0)){
               ++num;
            }
         }
      }
      return num;       // DUMMY CODE so skeleton compiles
   }
   
   
   /**
      Returns true iff (row,col) is a valid field location.  Row numbers and column numbers
      start from 0.
      @param row  row of the location to consider
      @param col  column of the location to consider
      @return whether (row, col) is a valid field location
   */
   public boolean inRange(int row, int col) {
      boolean result = row >= 0 && row < numRows && col >= 0 && col < numCols;
      return result;       // DUMMY CODE so skeleton compiles
   }
   
   
   /**
      Returns the number of rows in the field.
      @return number of rows in the field
   */  
   public int numRows() {
      return numRows;       // DUMMY CODE so skeleton compiles
   }
   
   
   /**
      Returns the number of columns in the field.
      @return number of columns in the field
   */    
   public int numCols() {
      return numCols;       // DUMMY CODE so skeleton compiles
   }
   
   
   /**
      Returns whether there is a mine in this square
      @param row  row of the location to check
      @param col  column of the location to check
      @return whether there is a mine in this square
      PRE: inRange(row, col)   
   */    
   public boolean hasMine(int row, int col) {
      return mineData[row][col];       // DUMMY CODE so skeleton compiles
   }
   
   
   /**
      Returns the number of mines you can have in this minefield.  For mines created with the 3-arg constructor,
      some of the time this value does not match the actual number of mines currently on the field.  See doc for that
      constructor, resetEmpty, and populateMineField for more details.
    * @return
    */
   public int numMines() {
      return numMines;       // DUMMY CODE so skeleton compiles
   }

   
   // <put private methods here>
   
   /*
    * To determine whether the mineData is valid 
    * @param mineData
    * return ture if it is a valid mineData
    */
   private boolean isValidMineData(boolean[][] mineData){
      if(mineData.length < 1 || (mineData.length == 1 && mineData[0].length < 1)){
         return false;
      }
      for(int i = 0; i < mineData.length - 1; ++i){
         if(mineData[i].length < 1 || mineData[i].length != mineData[i+1].length){
            return false;
         }
      }
      return true;
   }
   
}

