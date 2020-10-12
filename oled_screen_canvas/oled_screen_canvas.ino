#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(-1);

//Draw a circle.
void draw_circle(int x,int y, int radius, bool fill){
  if (fill)
    display.fillCircle(x, y, radius, WHITE);    
  else
    display.drawCircle(x, y, radius, WHITE);
  
}

//Draw a rectangle
void draw_rectangle(int x0, int y0, int x1, int y1, bool fill){
  if (fill)
    display.fillRect(x0, y0, x1, y1, WHITE);
  else    
    display.drawRect(x0, y0, x1, y1, WHITE);
}

//Draw a triangle
void draw_triangle(int x0,int y0, int x1, int y1, int x2, int y2,bool fill){
  if (fill)
    display.fillTriangle(x0, y0, x1, y1, x2, y2, WHITE);
  else
    display.drawTriangle(x0, y0, x1, y1, x2, y2, WHITE);  
}

//Write a text.
void draw_text(String str){
  display.println(str);
}

//Draw a pixel
void draw_pixel(int x,int y){
  display.drawPixel(x, y, WHITE);
}

//Change the font size.
void font_size(int num){
  display.setTextSize(num);
}

//Draw a line.
void draw_line(int x0,int y0, int x1, int y1){
  display.drawLine(x0, y0, x1, y1, WHITE);
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
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  clear();
  font_size(2);
  display.setTextColor(WHITE);
  cursor(0,0);
  //draw_text("Hola Damian :D");
  //draw_rectangle(10, 10, 10, 10,true);
  //draw_circle(10,10,5,true);
  //draw_triangle(30, 15, 0, 60, 60, 60,true);
  //draw_pixel(10,10);
  draw_line(0,0,20,20);
  display.display();
  delay(1000);

}

void loop() {}
