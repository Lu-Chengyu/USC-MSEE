import java.util.*;
/**
   This class tests the Bookshelf class.
   CS 455  Lab 4.
*/
public class BookshelfTester
{
   public static void main(String[] args)   {
       
      Bookshelf bookshelf1 = new Bookshelf();
      ArrayList<Integer> pileOfBooks1 = new ArrayList<Integer>();
      ArrayList<Integer> pileOfBooks2 = new ArrayList<Integer>();
      pileOfBooks2.add(1);
      pileOfBooks2.add(9);
      pileOfBooks2.add(20);
      Bookshelf bookshelf2 = new Bookshelf(pileOfBooks1);
      Bookshelf bookshelf3 = new Bookshelf(pileOfBooks2);

      // TEST EMPTY BOOKSHELF OBJECT

      System.out.println("After empty constructor:");
      System.out.println("The height of all books on the bookshelf [exp:[]]: " + bookshelf1.toString());
      System.out.println();

      // TEST NON-EMPTY BOOKSHELF OBJECT

      System.out.println("After non-empty constructor with empty ArrayList:");
      System.out.println("The height of all books on the bookshelf [exp:[]]: " + bookshelf2.toString());
      System.out.println();
      
      System.out.println("After non-empty constructor with non-empty ArrayList:");
      System.out.println("The height of all books on the bookshelf [exp:[1, 9, 20]]: " + bookshelf3.toString());
      System.out.println();
      
      // TEST addFront

      System.out.println("After addFront to empty Bookshelf:");
      bookshelf1.addFront(1);
      System.out.println("The height of all books on the bookshelf [exp:[1]]: " + bookshelf1.toString());
      System.out.println();
      
      System.out.println("After addFront to empty Bookshelf with non-empty ArrayList:");
      bookshelf2.addFront(1);
      System.out.println("The height of all books on the bookshelf [exp:[1]]: " + bookshelf2.toString());
      System.out.println();
      
      System.out.println("After addFront to non-empty Bookshelf:");
      bookshelf3.addFront(1);
      System.out.println("The height of all books on the bookshelf [exp:[1, 1, 9, 20]]: " + bookshelf3.toString());
      System.out.println();
      
      // TEST removeFront
      
      System.out.println("After removeFront to empty Bookshelf:");
      bookshelf1.removeFront();
      System.out.println("The height of all books on the bookshelf [exp:[]]: " + bookshelf1.toString());
      System.out.println();
      
      System.out.println("After removeFront to empty Bookshelf with non-empty ArrayList:");
      bookshelf2.removeFront();
      System.out.println("The height of all books on the bookshelf [exp:[]]: " + bookshelf2.toString());
      System.out.println();
      
      System.out.println("After removeFront to non-empty Bookshelf:");
      bookshelf3.removeFront();
      System.out.println("The height of all books on the bookshelf [exp:[1, 9, 20]]: " + bookshelf3.toString());
      System.out.println();
      
      // TEST addLast

      System.out.println("After addLast to empty Bookshelf:");
      bookshelf1.addLast(21);
      System.out.println("The height of all books on the bookshelf [exp:[21]]: " + bookshelf1.toString());
      System.out.println();
      
      System.out.println("After addLast to empty Bookshelf with non-empty ArrayList:");
      bookshelf2.addLast(21);
      System.out.println("The height of all books on the bookshelf [exp:[21]]: " + bookshelf2.toString());
      System.out.println();
      
      System.out.println("After addLast to non-empty Bookshelf:");
      bookshelf3.addLast(21);
      System.out.println("The height of all books on the bookshelf [exp:[1, 9, 20, 21]]: " + bookshelf3.toString());
      System.out.println();
      
      // TEST removeLast
      
      System.out.println("After removeLast to empty Bookshelf:");
      bookshelf1.removeLast();
      System.out.println("The height of all books on the bookshelf [exp:[]]: " + bookshelf1.toString());
      System.out.println();
      
      System.out.println("After removeLast to empty Bookshelf with non-empty ArrayList:");
      bookshelf2.removeLast();
      System.out.println("The height of all books on the bookshelf [exp:[]]: " + bookshelf2.toString());
      System.out.println();
      
      System.out.println("After removeLast to non-empty Bookshelf:");
      bookshelf3.removeLast();
      System.out.println("The height of all books on the bookshelf [exp:[1, 9, 20]]: " + bookshelf3.toString());
      System.out.println();
      
      // TEST getHeight
      
      System.out.println("Test getHeight of non-empty Bookshelf:");
      System.out.println("The height of 1st book on the non-empty bookshelf [exp:1]: " + bookshelf3.getHeight(0));
      System.out.println("The height of 3rd book on the non-empty bookshelf [exp:20]: " + bookshelf3.getHeight(2));
      System.out.println();
      
      // TEST size
      
      System.out.println("Test size of empty Bookshelf:");
      System.out.println("The size of empty bookshelf [exp:0]: " + bookshelf1.size());
      System.out.println();
      
      System.out.println("Test size of non-empty Bookshelf:");
      System.out.println("The size of non-empty bookshelf [exp:3]: " + bookshelf3.size());
      System.out.println();
      
      // TEST isSorted
      
      System.out.println("Test isSorted of empty Bookshelf:");
      System.out.println("The isSorted of empty bookshelf [exp:true]: " + bookshelf1.isSorted());
      System.out.println();
      
      System.out.println("Test isSorted of non-empty Bookshelf:");
      bookshelf3.addLast(1);
      System.out.println("The isSorted of non-empty bookshelf [exp:false]: " + bookshelf3.isSorted());
      System.out.println();
      
      System.out.println("Test isSorted of non-empty Bookshelf:");
      bookshelf3.removeLast();
      System.out.println("The isSorted of non-empty bookshelf [exp:true]: " + bookshelf3.isSorted());
      System.out.println();

      System.out.println("Test isSorted of non-empty Bookshelf:");
      bookshelf3.addFront(1);
      System.out.println("The isSorted of non-empty bookshelf [exp:true]: " + bookshelf3.isSorted());
      System.out.println();
      
      System.out.println("Test isSorted of non-empty Bookshelf:");
      bookshelf3.removeFront();
      System.out.println("The isSorted of non-empty bookshelf [exp:true]: " + bookshelf3.isSorted());
      System.out.println();
   }

}
