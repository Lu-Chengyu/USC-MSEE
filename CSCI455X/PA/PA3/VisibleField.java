// Name:Chengyu Lu
// USC NetID:luchengy
// CS 455 PA3
// Spring 2023


/**
  VisibleField class
  This is the data that's being displayed at any one point in the game (i.e., visible field, because it's what the
  user can see about the minefield). Client can call getStatus(row, col) for any square.
  It actually has data about the whole current state of the game, including  
  the underlying mine field (getMineField()).  Other accessors related to game status: numMinesLeft(), isGameOver().
  It also has mutators related to actions the player could do (resetGameDisplay(), cycleGuess(), uncover()),
  and changes the game state accordingly.
  
  It, along with the MineField (accessible in mineField instance variable), forms
  the Model for the game application, whereas GameBoardPanel is the View and Controller in the MVC design pattern.
  It contains the MineField that it's partially displaying.  That MineField can be accessed (or modified) from 
  outside this class via the getMineField accessor.  
 */
public class VisibleField {
   // ----------------------------------------------------------   
   // The following public constants (plus numbers mentioned in comments below) are the possible states of one
   // location (a "square") in the visible field (all are values that can be returned by public method 
   // getStatus(row, col)).
   
   // The following are the covered states (all negative values):
   public static final int COVERED = -1;   // initial value of all squares
   public static final int MINE_GUESS = -2;
   public static final int QUESTION = -3;

   // The following are the uncovered states (all non-negative values):
   
   // values in the range [0,8] corresponds to number of mines adjacent to this opened square
   
   public static final int MINE = 9;      // this loc is a mine that hasn't been guessed already (end of losing game)
   public static final int INCORRECT_GUESS = 10;  // is displayed a specific way at the end of losing game
   public static final int EXPLODED_MINE = 11;   // the one you uncovered by mistake (that caused you to lose)
   // ----------------------------------------------------------   

   /**
    * Representation invariants:
    * 1. mineField and status have the same size
    * 2. 0 <= numMinesLeft <= mineField.numRows() * mineField.numCols()
    */
   
   // <put instance variables here>
   private int[][] status;
   private int numMinesLeft;
   private MineField mineField;//
   
   /**
      Create a visible field that has the given underlying mineField.
      The initial state will have all the locations covered, no mines guessed, and the game
      not over.
      @param mineField  the minefield to use for for this VisibleField
    */
   public VisibleField(MineField mineField) {
      this.mineField = mineField;//
      status = new int[mineField.numRows()][mineField.numCols()];
      resetGameDisplay();//
   }
   
   
   /**
      Reset the object to its initial state (see constructor comments), using the same underlying
      MineField. 
   */     
   public void resetGameDisplay() {
      numMinesLeft = mineField.numMines();
      for(int i = 0; i < status.length; ++i){
         for(int j = 0; j < status[0].length; ++j){
            status[i][j] = COVERED;
         }
      }
   }
  
   
   /**
      Returns a reference to the mineField that this VisibleField "covers"
      @return the minefield
    */
   public MineField getMineField() {
      return mineField;       // DUMMY CODE so skeleton compiles
   }
   
   
   /**
      Returns the visible status of the square indicated.
      @param row  row of the square
      @param col  col of the square
      @return the status of the square at location (row, col).  See the public constants at the beginning of the class
      for the possible values that may be returned, and their meanings.
      PRE: getMineField().inRange(row, col)
    */
   public int getStatus(int row, int col) {
      assert isValidVisibleField(row, col);
      return status[row][col];       // DUMMY CODE so skeleton compiles
   }

   
   /**
      Returns the the number of mines left to guess.  This has nothing to do with whether the mines guessed are correct
      or not.  Just gives the user an indication of how many more mines the user might want to guess.  This value will
      be negative if they have guessed more than the number of mines in the minefield.     
      @return the number of mines left to guess.
    */
   public int numMinesLeft() {
      return numMinesLeft;       // DUMMY CODE so skeleton compiles

   }
 
   
   /**
      Cycles through covered states for a square, updating number of guesses as necessary.  Call on a COVERED square
      changes its status to MINE_GUESS; call on a MINE_GUESS square changes it to QUESTION;  call on a QUESTION square
      changes it to COVERED again; call on an uncovered square has no effect.  
      @param row  row of the square
      @param col  col of the square
      PRE: getMineField().inRange(row, col)
    */
   public void cycleGuess(int row, int col) {
      assert isValidVisibleField(row, col);
      if(status[row][col] == COVERED){
         status[row][col] = MINE_GUESS;
         --numMinesLeft;
      }
      else if(status[row][col] == MINE_GUESS){
         status[row][col] = QUESTION;
         ++numMinesLeft;
      }
      else if(status[row][col] == QUESTION){
         status[row][col] = COVERED;
      }
   }

   
   /**
      Uncovers this square and returns false iff you uncover a mine here.
      If the square wasn't a mine or adjacent to a mine it also uncovers all the squares in 
      the neighboring area that are also not next to any mines, possibly uncovering a large region.
      Any mine-adjacent squares you reach will also be uncovered, and form 
      (possibly along with parts of the edge of the whole field) the boundary of this region.
      Does not uncover, or keep searching through, squares that have the status MINE_GUESS. 
      Note: this action may cause the game to end: either in a win (opened all the non-mine squares)
      or a loss (opened a mine).
      @param row  of the square
      @param col  of the square
      @return false   iff you uncover a mine at (row, col)
      PRE: getMineField().inRange(row, col)
    */
   public boolean uncover(int row, int col) {
      assert isValidVisibleField(row, col);
      if(mineField.hasMine(row, col)){
         status[row][col] = EXPLODED_MINE;
         gameOver(false);
         return false;
      }
      uncoverAdjacentSquare(row, col);
      if(isGameOver()){
         gameOver(true);
      }
      return true;       // DUMMY CODE so skeleton compiles
   }
 
   
   /**
      Returns whether the game is over.
      (Note: This is not a mutator.)
      @return whether game has ended
    */
   public boolean isGameOver() {
      int numUncovered = 0;
      for(int i = 0; i < status.length; ++i){
         for(int j = 0; j < status[0].length; ++j){
            if(status[i][j] == MINE || status[i][j] == INCORRECT_GUESS || status[i][j] == EXPLODED_MINE){
               return true;
            }
            else if(status[i][j] >= 0 && status[i][j] <= 8){
               ++numUncovered;
            }
         }
      }
      if((mineField.numRows() * mineField.numCols() - numUncovered) == mineField.numMines()){
         return true;
      }
      return false;       // DUMMY CODE so skeleton compiles
   }
 
   
   /**
      Returns whether this square has been uncovered.  (i.e., is in any one of the uncovered states, 
      vs. any one of the covered states).
      @param row of the square
      @param col of the square
      @return whether the square is uncovered
      PRE: getMineField().inRange(row, col)
    */
   public boolean isUncovered(int row, int col) {
      assert isValidVisibleField(row, col);
      boolean result = (status[row][col] != COVERED && status[row][col] != MINE_GUESS && status[row][col] != QUESTION);
      return result;       // DUMMY CODE so skeleton compiles
   }
   
 
   // <put private methods here>
   
   /**
    * recursively uncover adjacent square
    * @param row
    * @param col
    */
   private void uncoverAdjacentSquare(int row, int col){
      if(isUncovered(row,col) || getStatus(row,col) == MINE_GUESS){
         return;
      }
      status[row][col] = mineField.numAdjacentMines(row, col);
      if(status[row][col] == 0){
         for(int i = -1; i <= 1; ++i){
            for(int j = -1; j <= 1; ++j){
               if(mineField.inRange(row+i,col+j) && !(i == 0 && j == 0)){
                  uncoverAdjacentSquare(row+i,col+j);
               }
            }
         }
      }
   }
   
   /**
    * set status when game over according to win or failure
    * @param win
    */
   private void gameOver(boolean win){
      for(int i = 0; i < status.length; i++){
         for(int j = 0; j < status[0].length; j++){
            if(win && mineField.hasMine(i, j)){
               status[i][j] = MINE_GUESS;
            }
            else if(status[i][j] == MINE_GUESS && !mineField.hasMine(i, j)){
               status[i][j] = INCORRECT_GUESS;
            }
            else if((status[i][j] == COVERED || status[i][j] == QUESTION) && mineField.hasMine(i, j)){
               status[i][j] = MINE;
            }
         }
      }
   }
   
/*
    * To determine whether the mineData is valid 
    * @param mineData
    * return ture if it is a valid mineData
    */
   private boolean isValidVisibleField(int row, int col){
      return getMineField().inRange(row, col);
   }
}
