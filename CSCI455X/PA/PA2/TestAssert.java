import java.util.*;
/**
   This class tests the Bookshelf class.
   CS 455  Lab 4.
*/
public class TestAssert
{
   public static void main(String[] args)   {
       
      ArrayList<Integer> pileOfBooks1 = new ArrayList<Integer>();
      pileOfBooks1.add(-1);
      pileOfBooks1.add(9);
      pileOfBooks1.add(20);
      ArrayList<Integer> pileOfBooks2 = new ArrayList<Integer>();
      pileOfBooks2.add(1);
      pileOfBooks2.add(9);
      pileOfBooks2.add(20);
      Bookshelf bookshelf1 = new Bookshelf(pileOfBooks1);
      Bookshelf bookshelf2 = new Bookshelf(pileOfBooks2);
   }
}