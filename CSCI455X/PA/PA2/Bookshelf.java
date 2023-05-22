// Name: Chengyu Lu
// USC NetID: luchengy
// CSCI455 PA2
// Spring 2023

import java.util.ArrayList;

/**
 * Class Bookshelf
 * Implements idea of arranging books into a bookshelf.
 * Books on a bookshelf can only be accessed in a specific way so books don’t fall down;
 * You can add or remove a book only when it’s on one of the ends of the shelf.
 * However, you can look at any book on a shelf by giving its location (starting at 0).
 * Books are identified only by their height; two books of the same height can be
 * thought of as two copies of the same book.
 */
public class Bookshelf {

   /**
    * Representation invariant:
    * <p>
    * <put rep. invar. comment here>
    * 1) book height must be larger than 0.
    */

   // <add instance variables here>
   private ArrayList<Integer> pileOfBooks;

   /**
    * Creates an empty Bookshelf object i.e. with no books
    */
   public Bookshelf() {
      pileOfBooks = new ArrayList<Integer>();
      assert isValidBookshelf();  // sample assert statement (you will be adding more of these calls)
   }

   /**
    * Creates a Bookshelf with the arrangement specified in pileOfBooks. Example
    * values: [20, 1, 9].
    * <p>
    * PRE: pileOfBooks contains an array list of 0 or more positive numbers
    * representing the height of each book.
    * @param pileOfBooks the initialization ArrayList<Integer> instance
    */
   public Bookshelf(ArrayList<Integer> pileOfBooks) {
      this.pileOfBooks = new ArrayList<Integer>(pileOfBooks);
      assert isValidBookshelf();
   }

   /**
    * Inserts book with specified height at the start of the Bookshelf, i.e., it
    * will end up at position 0.
    * <p>
    * PRE: height > 0 (height of book is always positive)
    * @param height the height of the input book
    */
   public void addFront(int height) {
      pileOfBooks.add(0, height);
      assert isValidBookshelf();
   }

   /**
    * Inserts book with specified height at the end of the Bookshelf.
    * <p>
    * PRE: height > 0 (height of book is always positive)
    * @param height the height of the input book
    */
   public void addLast(int height) {
      pileOfBooks.add(height);
      assert isValidBookshelf();
   }

   /**
    * Removes book at the start of the Bookshelf and returns the height of the
    * removed book.
    * <p>
    * PRE: this.size() > 0 i.e. can be called only on non-empty BookShelf
    */
   public int removeFront() {
      assert pileOfBooks.size() > 0;
      int output = pileOfBooks.get(0);
      pileOfBooks.remove(0);
      assert isValidBookshelf();
      return output;   // dummy code to get stub to compile

   }

   /**
    * Removes book at the end of the Bookshelf and returns the height of the
    * removed book.
    * <p>
    * PRE: this.size() > 0 i.e. can be called only on non-empty BookShelf
    */
   public int removeLast() {
      assert pileOfBooks.size() > 0;
      int output = pileOfBooks.get(pileOfBooks.size() - 1);
      pileOfBooks.remove(pileOfBooks.size() - 1);
      assert isValidBookshelf();
      return output;   // dummy code to get stub to compile      
   }

   /*
    * Gets the height of the book at the given position.
    *
    * PRE: 0 <= position < this.size()
    * @param position the position of the book user want
    */
   public int getHeight(int position) {
      assert pileOfBooks.size() > position && position >= 0;
      int output = pileOfBooks.get(position);
      assert isValidBookshelf();
      return output;   // dummy code to get stub to compile

   }

   /**
    * Returns number of books on the this Bookshelf.
    */
   public int size() {
      int output = pileOfBooks.size();
      assert isValidBookshelf();
      return output;   // dummy code to get stub to compile

   }

   /**
    * Returns string representation of this Bookshelf. Returns a string with the height of all
    * books on the bookshelf, in the order they are in on the bookshelf, using the format shown
    * by example here:  “[7, 33, 5, 4, 3]”
    */
   public String toString() {
      String output = "[";
      for (int i = 0; i < pileOfBooks.size(); ++i) {
         output += pileOfBooks.get(i);
         if (i != pileOfBooks.size() - 1) {
            output += ", ";
         }
      }
      output += "]";
      assert isValidBookshelf();
      return output;   // dummy code to get stub to compile
   }

   /**
    * Returns true iff the books on this Bookshelf are in non-decreasing order.
    * (Note: this is an accessor; it does not change the bookshelf.)
    */
   public boolean isSorted() {
      for (int i = 0; i < pileOfBooks.size() - 1; ++i) {
         if (pileOfBooks.get(i) >= pileOfBooks.get(i + 1)) {
            return false;
         }
      }
      assert isValidBookshelf();
      return true;  // dummy code to get stub to compile
   }

   /**
    * Returns true iff the Bookshelf data is in a valid state.
    * (See representation invariant comment for more details.)
    */
   private boolean isValidBookshelf() {
      for (int i = 0; i < pileOfBooks.size(); ++i) {
         if (pileOfBooks.get(i) <= 0) {
            return false;
         }
      }
      return true;  // dummy code to get stub to compile
   }

}