// Name:Chengyu Lu
// USC NetID:luchengy
// CS 455 PA1
// Spring 2023

import java.util.Scanner;

/**
 * CoinTossSimulatorTester class
 * Several test units.
 * 
 * javac CoinTossSimulator*.java
 * java CoinTossSimulatorTester
 */
public class CoinTossSimulatorTester{
   
   /**
      Creates test cases.
  
      @param args  for main function
   */
   public static void main(String[] args){
      CoinTossSimulator test = new CoinTossSimulator();
      
      System.out.println("After constructor:");
      System.out.println("Number of trials [exp:0]: " + test.getNumTrials());
      System.out.println("Two-head tosses: " + test.getTwoHeads());
      System.out.println("Two-tail tosses: " + test.getTwoTails());
      System.out.println("One-head one-tail tosses: " + test.getHeadTails());
      System.out.print("Tosses add up correctly? ");
      System.out.println(test.getTwoHeads() + test.getTwoTails() + test.getHeadTails() == 0);
      System.out.println("");
      
      test.run(1);
      System.out.println("After run(1):");
      System.out.println("Number of trials [exp:1]: " + test.getNumTrials());
      System.out.println("Two-head tosses: " + test.getTwoHeads());
      System.out.println("Two-tail tosses: " + test.getTwoTails());
      System.out.println("One-head one-tail tosses: " + test.getHeadTails());
      System.out.print("Tosses add up correctly? ");
      System.out.println(test.getTwoHeads() + test.getTwoTails() + test.getHeadTails() == 1);
      System.out.println("");
      
      test.run(10);
      System.out.println("After run(10):");
      System.out.println("Number of trials [exp:11]: " + test.getNumTrials());
      System.out.println("Two-head tosses: " + test.getTwoHeads());
      System.out.println("Two-tail tosses: " + test.getTwoTails());
      System.out.println("One-head one-tail tosses: " + test.getHeadTails());
      System.out.print("Tosses add up correctly? ");
      System.out.println(test.getTwoHeads() + test.getTwoTails() + test.getHeadTails() == 11);
      System.out.println("");
      
      test.run(100);
      System.out.println("After run(100):");
      System.out.println("Number of trials [exp:111]: " + test.getNumTrials());
      System.out.println("Two-head tosses: " + test.getTwoHeads());
      System.out.println("Two-tail tosses: " + test.getTwoTails());
      System.out.println("One-head one-tail tosses: " + test.getHeadTails());
      System.out.print("Tosses add up correctly? ");
      System.out.println(test.getTwoHeads() + test.getTwoTails() + test.getHeadTails() == 111);
      System.out.println("");
      
      test.reset();
      System.out.println("After reset:");
      System.out.println("Number of trials [exp:0]: " + test.getNumTrials());
      System.out.println("Two-head tosses: " + test.getTwoHeads());
      System.out.println("Two-tail tosses: " + test.getTwoTails());
      System.out.println("One-head one-tail tosses: " + test.getHeadTails());
      System.out.print("Tosses add up correctly? ");
      System.out.println(test.getTwoHeads() + test.getTwoTails() + test.getHeadTails() == 0);
      System.out.println("");
      
      test.run(1000);
      System.out.println("After run(1000):");
      System.out.println("Number of trials [exp:1000]: " + test.getNumTrials());
      System.out.println("Two-head tosses: " + test.getTwoHeads());
      System.out.println("Two-tail tosses: " + test.getTwoTails());
      System.out.println("One-head one-tail tosses: " + test.getHeadTails());
      System.out.print("Tosses add up correctly? ");
      System.out.println(test.getTwoHeads() + test.getTwoTails() + test.getHeadTails() == 1000);
      System.out.println("");
   }
}
