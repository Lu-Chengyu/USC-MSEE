// Name:Chengyu Lu
// USC NetID:luchengy
// CS 455 PA1
// Spring 2023

import java.util.Random;
/**
 * class CoinTossSimulator
 * 
 * Simulates trials of repeatedly tossing two coins and allows the user to access the
 * cumulative results.
 * 
 * NOTE: we have provided the public interface for this class.  Do not change
 * the public interface.  You can add private instance variables, constants, 
 * and private methods to the class.  You will also be completing the 
 * implementation of the methods given. 
 * 
 * Invariant: getNumTrials() = getTwoHeads() + getTwoTails() + getHeadTails()
 * 
 */
public class CoinTossSimulator {

   private int twoHeads;
   private int headTails;
   private int twoTails;
   private int numTrials;

   /**
      Creates a coin toss simulator with no trials done yet.
   */
   public CoinTossSimulator() {
      twoHeads = 0;
      headTails = 0;
      twoTails = 0;
      numTrials = 0;
   }


   /**
      Runs the simulation for numTrials more trials. Multiple calls to this method
      without a reset() between them *add* these trials to the current simulation.
      
      @param numTrials  number of trials to for simulation; must be >= 1
    */
   public void run(int numTrials) {
      
      this.numTrials = numTrials;
      
      int coinFirst;
      int coinSecond;
      
      Random coinToss = new Random();
      for(int i = 0; i < this.numTrials; ++i)
      {
         coinFirst = coinToss.nextInt(2);
         coinSecond = coinToss.nextInt(2);
         if(coinFirst == 1 && coinSecond == 1)
         {
            twoHeads++;
         }
         else if((coinFirst == 1 && coinSecond != 1) || (coinFirst != 1 && coinSecond == 1))
         {
            headTails++;
         }
         else
         {
            twoTails++;
         }
      }
   }


   /**
      Get number of trials performed since last reset.
   */
   public int getNumTrials() {
       return (twoHeads + headTails + twoTails); // DUMMY CODE TO GET IT TO COMPILE
   }


   /**
      Get number of trials that came up two heads since last reset.
   */
   public int getTwoHeads() {
       return twoHeads; // DUMMY CODE TO GET IT TO COMPILE
   }


   /**
     Get number of trials that came up two tails since last reset.
   */  
   public int getTwoTails() {
       return twoTails; // DUMMY CODE TO GET IT TO COMPILE
   }


   /**
     Get number of trials that came up one head and one tail since last reset.
   */
   public int getHeadTails() {
       return headTails; // DUMMY CODE TO GET IT TO COMPILE
   }


   /**
      Resets the simulation, so that subsequent runs start from 0 trials done.
    */
   public void reset() {
      twoHeads = 0;
      headTails = 0;
      twoTails = 0;
      numTrials = 0;
   }

}
