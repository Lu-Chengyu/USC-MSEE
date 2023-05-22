// Name:Chengyu Lu
// USC NetID:luchengy
// CS 455 PA1
// Spring 2023

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import javax.swing.JComponent;

/**
 * CoinSimComponent class
 * This component draws three bar shapes.
 * 
 */
public class CoinSimComponent extends JComponent{  
   private int callCount;
   private int trials;
   private CoinTossSimulator coinToss = new CoinTossSimulator();
   
   /**
      Creates CoinSimComponent.  You give the number of trials.
  
      @param trials  the number of trials
   */
   public CoinSimComponent(int trials){
      callCount = 0;
      this.trials = trials;
      coinToss.run(trials);
   }
   
   /**
      Draw the Component.
      @param g  the graphics context
   */
   public void paintComponent(Graphics g){  
      Graphics2D g2 = (Graphics2D) g;
      
      final int BAR_WIDTH = 50;
      final int VERTICAL_BUFFER = 20;
      int bottom = getHeight() - VERTICAL_BUFFER;
      int twoHeadsLeft = getWidth() / 4 * 1 - BAR_WIDTH / 2;
      int headTailsLeft = getWidth() / 4 * 2 - BAR_WIDTH / 2;
      int twoTailsLeft = getWidth() / 4 * 3 - BAR_WIDTH / 2;
      int twoHeadsApplicationHeight = coinToss.getTwoHeads();
      int headTailsApplicationHeight = coinToss.getHeadTails();
      int twoTailsApplicationHeight = coinToss.getTwoTails();
      double scale = (double)(getHeight() - 2 * VERTICAL_BUFFER) / coinToss.getNumTrials();
      Color twoHeadsColor = Color.RED;
      Color headTailsColor = Color.GREEN;
      Color twoTailsColor = Color.BLUE;
      String twoHeadsLabel = "Two Heads: " + coinToss.getTwoHeads() + " (" + Math.round((float)coinToss.getTwoHeads() / (float)coinToss.getNumTrials() * 100) + "%)";
      String headTailsLabel = "A Head and a Tail: " + coinToss.getHeadTails() + " (" + Math.round((float)coinToss.getHeadTails() / (float)coinToss.getNumTrials() * 100) + "%)";
      String twoTailsLabel = "Two Tails: " + coinToss.getTwoTails() + " (" + Math.round((float)coinToss.getTwoTails() / (float)coinToss.getNumTrials() * 100) + "%)";
           
      // the following two lines are for instrumentation
      callCount++;
      System.out.println("Called paintComponent(" + callCount + ")");

      Bar barTwoHeads = new Bar(bottom, twoHeadsLeft, BAR_WIDTH, twoHeadsApplicationHeight, scale, twoHeadsColor, twoHeadsLabel);
      Bar barHeadTails = new Bar(bottom, headTailsLeft, BAR_WIDTH, headTailsApplicationHeight, scale, headTailsColor, headTailsLabel);      
      Bar barTwoTails = new Bar(bottom, twoTailsLeft, BAR_WIDTH, twoTailsApplicationHeight, scale, twoTailsColor, twoTailsLabel);
      
      barTwoHeads.draw(g2);
      barHeadTails.draw(g2); 
      barTwoTails.draw(g2);
   }
}
