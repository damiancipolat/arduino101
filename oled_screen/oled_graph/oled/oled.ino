/*
  Update history.
  -21.3.2017
    -Fixed error in code that caused screen colours to be inverted. Added option to enable inverting, if user so wants. Credit for Ralp Canas for mentioning this bug.
  -7.5.2017
    -Addded functions to allow changing scrolling direction (Joe Nights' suggestion) and  dot/filled mode. Also, slope colour can be changed now too.
*/


/*********************************************************************
  This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

  This example is for a 128x32 size display using I2C to communicate
  3 pins are required to interface (2 I2C and one reset)

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada  for Adafruit Industries.
  BSD license, check license.txt for more information
  All text above, and the splash screen must be included in any redistribution
*********************************************************************/


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4

Adafruit_SSD1306 display(OLED_RESET);
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
byte count;
byte sensorArray[128];
byte drawHeight;

/*following functions controls scrolling direction (left/right) and drawing mode (dot/filled)
  These commands are NOT case sensitive, code understands in both capitals and non-capitals of these commands to make it more user friendly.
*/
char filled = 'F'; //decide either filled or dot display (D=dot, any else filled)
char drawDirection = 'R'; //decide drawing direction, from right or from left (L=from left to right, any else from right to left)
char slope = 'W'; //slope colour of filled mode white or black slope (W=white, any else black. Well, white is blue in this dispay but you get the point)
void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)

  for (count = 0; count <= 128; count++) //zero all elements
  {
    sensorArray[count] = 0;
  }
}


void loop()
{
  drawHeight = map(analogRead(A0), 0, 1023, 0, 32 );
  sensorArray[0] = drawHeight;

  for (count = 1; count <= 80; count++ )
  {
    if (filled == 'D' || filled == 'd')
    {
      if (drawDirection == 'L' || drawDirection == 'l')
      {
        display.drawPixel(count, 32 - sensorArray[count - 1], WHITE);
      }
      else //else, draw dots from right to left
      {
        display.drawPixel(80 - count, 32 - sensorArray[count - 1], WHITE);
      }
    }


    

    else
    {
      if (drawDirection == 'L' || drawDirection == 'l')
      {
        if (slope == 'W' || slope == 'w')
        {
          display.drawLine(count, 32, count, 32 - sensorArray[count - 1], WHITE);
        }
        else
        {
          display.drawLine(count, 1, count, 32 - sensorArray[count - 1], WHITE);

        }
      }



      else
      {
        if (slope == 'W' || slope == 'w')
        {
          display.drawLine(80 - count, 32, 80 - count, 32 - sensorArray[count - 1], WHITE);
        }
        else
        {
          display.drawLine(80 - count, 1, 80 - count, 32 - sensorArray[count - 1], WHITE);
        }
      }
    }
  }

  drawAxises();
  display.display();  //needed before anything is displayed
  display.clearDisplay(); //clear before new drawing

  for (count = 80; count >= 2; count--) // count down from 160 to 2
  {
    sensorArray[count - 1] = sensorArray[count - 2];
  }

}

void drawAxises()  //separate to keep stuff neater. This controls ONLY drawing background!
{
  display.setCursor(90, 0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print(drawHeight);
  display.setCursor(90, 8);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("KM/h");


  display.drawLine(0, 0, 0, 32, WHITE);
  display.drawLine(80, 0, 80, 32, WHITE);

  for (count = 0; count < 40; count += 10)
  {
    display.drawLine(80, count, 75, count, WHITE);
    display.drawLine(0, count, 5, count, WHITE);
  }

  for (count = 10; count < 80; count += 10)
  {
    display.drawPixel(count, 0 , WHITE);
    display.drawPixel(count, 31 , WHITE);
  }
}
