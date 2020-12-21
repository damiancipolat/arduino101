#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(-1);

//Draw a circle.
void circle(int x,int y, int radius){
  display.drawCircle(x, y, radius, WHITE);
}

//Draw a rectangle
void draw_rectangle(int x0, int y0, int x1, int y1){
  display.drawRect(x0, y0, x1, y1, WHITE);
}

//Write a text.
void draw_text(String str){
  display.println(str);
}

//Change the font size.
void font_size(int num){
  display.setTextSize(num);
}

//Set the cursor position in the screen
void cursor(int x,int y){
  display.setCursor(x,y);  
}

//Clear the screen.
void clear(){
  display.clearDisplay();
}
  
void setup()   
{              
  // initialize with the I2C addr 0x3C
  Wire.begin(2,0);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  clear();
  font_size(2);
  display.setTextColor(WHITE);
  cursor(0,0);
  //draw_text("Hola Damian :D");
  //draw_rectangle(10, 10, 10, 10);
  circle(0,0,5);
  display.display();
  delay(1000);

}

void loop() {}
