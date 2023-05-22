// Name:Chengyu Lu
// USC NetID:luchengy
// CS 455 PA1
// Spring 2023

import javax.swing.JFrame;
import java.util.Scanner;

/**
 * CoinSimViewer class
 * Contains the main method. Prompts for the number of trials.
 * 
 * javac @CoinSimViewer.list
 * java CoinSimViewer
 */
public class CoinSimViewer
{
   /**
      Main function. Prompts for the number of trials. Draw the frame.
  
      @param args  for main function
   */
   public static void main(String[] args)
   {
      Scanner in = new Scanner(System.in);
      System.out.print("Enter number of trials: ");
      int trials = in.nextInt();
      while (trials < 1) 
      {
         System.out.println("ERROR: Number entered must be greater than 0.");
         System.out.print("Enter number of trials: ");
         trials = in.nextInt();
      }
      
      JFrame frame = new JFrame();
      frame.setSize(800, 500);
      frame.setTitle("CoinSim");
      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      CoinSimComponent component = new CoinSimComponent(trials);
      frame.add(component);
      frame.setVisible(true);
   }
}
