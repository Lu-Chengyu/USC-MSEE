// Name: Chengyu Lu
// USC NetID: luchengy
// CSCI455 PA2
// Spring 2023

import java.util.Scanner;
import java.util.ArrayList;

/**
 * Class BookshelfKeeperProg
 * <p>
 * Enables user to perform a series of pickPos and putHeight operations on a 
 * bookshelf in an interactive mode with user commands called pick and put.
 */
public class BookshelfKeeperProg {

   /**
    * Enables the user to input a series of number to initialize a bookshelf. 
    * Enables the user to input a series of commands and numbers to modify the bookshelf. 
    * @param String[] for main function
    */
   public static void main(String[] args) {
      System.out.println("Please enter initial arrangement of books followed by newline:");
      Scanner in = new Scanner(System.in);
      BookshelfKeeper bookshelfKeeper = testInitialInput(in);
      if (bookshelfKeeper != null) {
         System.out.println("Type pick <index> or put <height> followed by newline. Type end to exit.");
         while (bookshelfKeeper != null) {
            bookshelfKeeper = testCommands(in, bookshelfKeeper);
         }
      }
      System.out.println("Exiting Program.");
   }

   /**
    * Helps the user to test whether the input numbers are valid or not for a bookshelf.
    * Helps the user to initialize the bookshelf.
    * @param in Obtains the user input for the bookshelf initialization.
    */
   private static BookshelfKeeper testInitialInput(Scanner in) {
      ArrayList<Integer> booksArray = new ArrayList<>();
      String initialInput = in.nextLine();
      Scanner temp = new Scanner(initialInput);
      while (temp.hasNextInt()) {
         int height = temp.nextInt();
         if (height <= 0) {
            System.out.println("ERROR: Height of a book must be positive.");
            temp.close();
            return null;
         }
         if (booksArray.size() != 0) {
            if (height < booksArray.get(booksArray.size() - 1)) {
               System.out.println("ERROR: Heights must be specified in non-decreasing order.");
               temp.close();
               return null;
            }
         }
         booksArray.add(height);
      }
      Bookshelf bookshelf = new Bookshelf(booksArray);
      BookshelfKeeper bookshelfKeeper = new BookshelfKeeper(bookshelf);
      System.out.println(bookshelfKeeper.toString());
      temp.close();
      return bookshelfKeeper;
   }

   /**
    * Helps the user to test whether the input commands and numbers are valid or not.
    * Helps the user to use the input commands and numbers to modify the bookshelf.
    * @param in Obtains the user input for the commands and parameters.
    * @param bookshelfKeeper The BookshelfKeeper being modified by the commonds and parameters.
    */
   private static BookshelfKeeper testCommands(Scanner in, BookshelfKeeper bookshelfKeeper) {
      String commandsInput = in.nextLine();
      Scanner temp = new Scanner(commandsInput);
      while (temp.hasNext()) {
         String command = temp.next();
         if (command.equals("put")) {
            int height = temp.nextInt();
            if (height <= 0) {
               System.out.println("ERROR: Height of a book must be positive.");
               temp.close();
               return null;
            }
            bookshelfKeeper.putHeight(height);
            System.out.println(bookshelfKeeper.toString());
         } else if (command.equals("pick")) {
            int position = temp.nextInt();
            if (position >= bookshelfKeeper.getNumBooks()) {
               System.out.println("ERROR: Entered pick operation is invalid on this shelf.");
               temp.close();
               return null;
            }
            bookshelfKeeper.pickPos(position);
            System.out.println(bookshelfKeeper.toString());
         } else if (command.equals("end")) {
            temp.close();
            return null;
         } else {
            System.out.println("ERROR: Invalid command. Valid commands are pick, put, or end.");
            temp.close();
            return null;
         }
      }
      temp.close();
      return bookshelfKeeper;
   }
}