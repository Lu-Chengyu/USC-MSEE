// Name:Chengyu Lu
// USC NetID:luchengy
// CS 455 PA1
// Spring 2023

// we included the import statements for you

import java.awt.Font;
import java.awt.Color;
import java.awt.Rectangle;
import java.awt.Graphics2D;
import java.awt.geom.Rectangle2D;
import java.awt.font.FontRenderContext;

/**
 * Bar class
 * A labeled bar that can serve as a single bar in a bar graph.
 * The text for the label is centered under the bar.
 * 
 * NOTE: we have provided the public interface for this class. Do not change
 * the public interface. You can add private instance variables, constants,
 * and private methods to the class. You will also be completing the
 * implementation of the methods given.
 * 
 */
public class Bar {
   private int xLeft;
   private int yTop;
   private int barWidth;
   private int barHeight;
   private Color barColor;
   private String barLabel;
   
   /**
      Creates a labeled bar.  You give the height of the bar in application
      units (e.g., population of a particular state), and then a scale for how
      tall to display it on the screen (parameter scale).
  
      @param bottom  location of the bottom of the bar
      @param left  location of the left side of the bar
      @param width  width of the bar (in pixels)
      @param applicationHeight  height of the bar in application units
      @param scale  how many pixels per application unit
      @param color  the color of the bar
      @param label  the label under the bar
   */
   public Bar(int bottom, int left, int width, int applicationHeight, 
              double scale, Color color, String label) {
      xLeft = left;
      yTop = (int)(bottom - applicationHeight * scale);
      barWidth = width;
      barHeight = (int)(applicationHeight * scale);
      barColor = color;
      barLabel = label;
   }
   
   /**
      Draw the labeled bar.
      @param g2  the graphics context
   */
   public void draw(Graphics2D g2) {

      Rectangle body = new Rectangle(xLeft, yTop, barWidth, barHeight); 
      g2.setColor(barColor);
      g2.fill(body);
         
      Font font = g2.getFont(); 
      FontRenderContext context = g2.getFontRenderContext(); 
      Rectangle2D labelBounds = font.getStringBounds(barLabel, context); 
      int widthOfLabel = (int) labelBounds.getWidth(); 
      int heightOfLabel = (int) labelBounds.getHeight();
      int labelLeft = xLeft + barWidth/2 - widthOfLabel/2;
      int labelTop = yTop + barHeight + heightOfLabel;
      if(barHeight != 0)
      {
         g2.draw(body);
      }
      Color labelColor = Color.BLACK;
      g2.setColor(labelColor);
      g2.drawString(barLabel, labelLeft,labelTop);

   }
}
