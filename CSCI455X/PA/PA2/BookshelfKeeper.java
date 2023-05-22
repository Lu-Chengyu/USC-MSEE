// Name: Chengyu Lu
// USC NetID: luchengy
// CSCI455 PA2
// Spring 2023

/**
 * Class BookshelfKeeper
 * <p>
 * Enables users to perform efficient putPos or pickHeight operation on a bookshelf of books kept in
 * non-decreasing order by height, with the restriction that single books can only be added
 * or removed from one of the two *ends* of the bookshelf to complete a higher level pick or put
 * operation.  Pick or put operations are performed with minimum number of such adds or removes.
 */
import java.util.ArrayList;
public class BookshelfKeeper {

   /**
    * Representation invariant:
    * <p>
    * <put rep. invar. comment here>
    * 1) numMutators is the number of bookshelf mutator calls made to perform the last pick or put operation
    * 2) numTotal is the total number of such calls made since we created this BookshelfKeeper
    * 3) numMutators <= numTotal
    * 4) books in sortedBookshelf are in non-decreasing height order
    */

   // <add instance variables here>
   private Bookshelf sortedBookshelf;
   private int numMutators;
   private int numTotal;


   /**
    * Creates a BookShelfKeeper object with an empty bookshelf
    */
   public BookshelfKeeper() {
      numTotal = 0;
      numMutators = 0;
      sortedBookshelf = new Bookshelf();
      assert isValidBookshelfKeeper();
   }

   /**
    * Creates a BookshelfKeeper object initialized with the given sorted bookshelf.
    * Note: method does not make a defensive copy of the bookshelf.
    * <p>
    * PRE: sortedBookshelf.isSorted() is true.
    * @param sortedBookshelf  the initialization Bookshelf instance
    */
   public BookshelfKeeper(Bookshelf sortedBookshelf) {
      numTotal = 0;
      numMutators = 0;
      this.sortedBookshelf = sortedBookshelf;
      assert isValidBookshelfKeeper();
   }

   /**
    * Removes a book from the specified position in the bookshelf and keeps bookshelf sorted
    * after picking up the book.
    * <p>
    * Returns the number of calls to mutators on the contained bookshelf used to complete this
    * operation. This must be the minimum number to complete the operation.
    * <p>
    * PRE: 0 <= position < getNumBooks()
    * @param position  the location of the book on the bookshelf
    */
   public int pickPos(int position) {
      assert 0 <= position && position < getNumBooks();
      Bookshelf tempBookshelf = new Bookshelf();
      if (position < getNumBooks() - 1 - position) {
         for (int i = 0; i < position; ++i) {
            tempBookshelf.addLast(sortedBookshelf.removeFront());
         }
         sortedBookshelf.removeFront();
         for (int i = tempBookshelf.size() - 1; i >= 0; --i) {
            sortedBookshelf.addFront(tempBookshelf.removeLast());
         }
         numMutators = (position + 1) * 2 - 1;
      } else {
         for (int i = getNumBooks() - 1; i > position; --i) {
            tempBookshelf.addFront(sortedBookshelf.removeLast());
         }
         sortedBookshelf.removeLast();
         for (int i = tempBookshelf.size() - 1; i >= 0; --i) {
            sortedBookshelf.addLast(tempBookshelf.removeFront());
         }
         numMutators = (getNumBooks() - position) * 2 + 1;
      }
      numTotal += numMutators;
      assert isValidBookshelfKeeper();
      return numMutators;   // dummy code to get stub to compile
   }

   /**
    * Inserts book with specified height into the shelf.  Keeps the contained bookshelf sorted
    * after the insertion.
    * <p>
    * Returns the number of calls to mutators on the contained bookshelf used to complete this
    * operation. This must be the minimum number to complete the operation.
    * <p>
    * PRE: height > 0
    * @param height  the height of the input book
    */
   public int putHeight(int height) {
      assert height > 0;
      int backDistance = findBackDistance(height);
      int frontDistance = findFrontDistance(height);
      ArrayList<Integer> temp = new ArrayList<>();
      if(frontDistance < backDistance){
         for(int i = 0; i < frontDistance; ++i){
            temp.add(sortedBookshelf.removeFront());
         }
         temp.add(height);
         for(int i = temp.size() - 1; i >= 0; --i){
            sortedBookshelf.addFront(temp.get(i));
         }
         numMutators = frontDistance * 2 + 1;
      }
      else{
         for(int i = 0; i < backDistance; ++i){
            temp.add(sortedBookshelf.removeLast());
         }
         temp.add(height);
         for(int i = temp.size() - 1; i >= 0; i--){
            sortedBookshelf.addLast(temp.get(i));
         }
         numMutators = backDistance * 2 + 1;
      }
      numTotal += numMutators;
      assert isValidBookshelfKeeper();
      return numTotal;   // dummy code to get stub to compile
   }

   /**
    * Returns the total number of calls made to mutators on the contained bookshelf
    * so far, i.e., all the ones done to perform all of the pick and put operations
    * that have been requested up to now.
    */
   public int getTotalOperations() {
      assert isValidBookshelfKeeper();
      return numTotal;   // dummy code to get stub to compile
   }

   /**
    * Returns the number of books on the contained bookshelf.
    */
   public int getNumBooks() {
      int output = sortedBookshelf.size();
      assert isValidBookshelfKeeper();
      return output;   // dummy code to get stub to compile
   }

   /**
    * Returns string representation of this BookshelfKeeper. Returns a String containing height
    * of all books present in the bookshelf in the order they are on the bookshelf, followed
    * by the number of bookshelf mutator calls made to perform the last pick or put operation,
    * followed by the total number of such calls made since we created this BookshelfKeeper.
    * <p>
    * Example return string showing required format: “[1, 3, 5, 7, 33] 4 10”
    */
   public String toString() {
      String output = "";
      output += sortedBookshelf.toString();
      output += " ";
      output += numMutators;
      output += " ";
      output += numTotal;
      assert isValidBookshelfKeeper();
      return output;   // dummy code to get stub to compile
   }

   /**
    * Returns true iff the BookshelfKeeper data is in a valid state.
    * (See representation invariant comment for details.)
    */
   private boolean isValidBookshelfKeeper() {
      boolean output = sortedBookshelf.isSorted() && numMutators <= numTotal;
      return output;  // dummy code to get stub to compile
   }

   /**
    * Returns the distance of the fist location from front where the book can be inserted
    * @param height  the height of the input book
    */
   private int findFrontDistance(int height) {
      int frontBound = 0;
      for(int i = 0; i < sortedBookshelf.size(); ++i){
         if(height <= sortedBookshelf.getHeight(i)){
            break;
         }
         frontBound++;
      }
      return frontBound;
   }

   /**
    * Returns the distance of the fist location from back where the book can be inserted
    * @param height  the height of the input book
    */
   private int findBackDistance(int height) {
      int backBound = 0;
      for(int i = sortedBookshelf.size() - 1; i >= 0; --i){
         if(sortedBookshelf.getHeight(i) <= height){
            break;
         }
         backBound++;
      }
      return backBound;
   }

}