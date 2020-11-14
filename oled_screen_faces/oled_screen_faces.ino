#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Set display
Adafruit_SSD1306 display(128,64, &Wire,4);

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
}

void draw_eyes_1()
{
  int x = display.width()/2;
  int y = display.height()/2;

  for (int i=0;i<=5;i++){
    clear();
    draw_circle(x-25,y-15, 1+i, true);
    draw_circle(x+25,y-15, 1+i, true);
    display.display();
    delay(30);
  }
}

void draw_eyes_2()
{
  int x = display.width()/2;
  int y = display.height()/2;

  for (int i=5;i>=0;i--){
    clear();
    draw_circle(x-25,y-15, 1+i, true);
    draw_circle(x+25,y-15, 1+i, true);
    display.display();
    delay(30);
  }
}

void draw_eyes_3()
{
  int x = display.width()/2;
  int y = display.height()/2;

  for (int i=0;i<=5;i++){
    clear();
    draw_circle(x-25,(y-15)-i, 5, true);
    draw_circle(x+25,(y-15)-i, 5, true);
    display.display();
    delay(60);
  }

  for (int i=5;i>=0;i--){
    clear();
    draw_circle(x-25,(y-15)-i, 5, true);
    draw_circle(x+25,(y-15)-i, 5, true);
    display.display();
    delay(60);
  }
    
}

void draw_eyes_4()
{
  int x = display.width()/2;
  int y = display.height()/2;

  for (int i=0;i<=10;i++){
    clear();
    draw_circle((x-25)+i,y-15, 5, true);
    draw_circle((x+25)+i,y-15, 5, true);
    display.display();
    delay(50);
  }

  for (int i=10;i>=0;i--){
    clear();
    draw_circle((x-25)+i,y-15, 5, true);
    draw_circle((x+25)+i,y-15, 5, true);
    display.display();
    delay(50);
  }
}

void draw_eyes_5()
{
  int x = display.width()/2;
  int y = display.height()/2;

  for (int i=0;i<=10;i++){
    clear();
    draw_circle((x-25)-i,y-15, 5, true);
    draw_circle((x+25)-i,y-15, 5, true);
    display.display();
    delay(50);
  }

  for (int i=10;i>=0;i--){
    clear();
    draw_circle((x-25)-i,y-15, 5, true);
    draw_circle((x+25)-i,y-15, 5, true);
    display.display();
    delay(50);
  }
}

void draw_eyes_6()
{
  int x = display.width()/2;
  int y = display.height()/2;

  for (int i=0;i<=15;i++){
    clear();
    draw_circle(x-25,y-10, 5+i, true);
    draw_circle(x+25,y-10, 5+i, true);
    display.display();
    delay(1);
  }
}


void draw_eyes_7()
{
  int x = display.width()/2;
  int y = display.height()/2;

  for (int i=0;i<=10;i++){
    clear();
    draw_circle((x-25)-i,y-15, 5, true);
    draw_circle((x+25)+i,y-15, 5, true);
    display.display();
    delay(10);
  }

  for (int i=10;i>=0;i--){
    clear();
    draw_circle((x-25)-i,y-15, 5, true);
    draw_circle((x+25)+i,y-15, 5, true);
    display.display();
    delay(10);
  }
    
}


void draw_eyes_8()
{
  int x = display.width()/2;
  int y = display.height()/2;

  for (int i=-10;i<=10;i++){
    clear();
    draw_circle(x-25,(y-15)-i, 5, true);
    draw_circle(x+25,(y-15)+i, 5, true);
    display.display();
    delay(5);
  }

  for (int i=10;i>=-10;i--){
    clear();
    draw_circle(x-25,(y-15)-i, 5, true);
    draw_circle(x+25,(y-15)+i, 5, true);
    display.display();
    delay(5);
  }
}

void draw_eyes()
{
  int x = display.width()/2;
  int y = display.height()/2;  
  
  draw_circle(x-25,y-15, 5, true);
  draw_circle(x+25,y-15, 5, true);  
}

void draw(){
  clear();
  draw_eyes();
  draw_eyes_1();
  draw_eyes_2();
  draw_eyes_3();
  draw_eyes_4();
  draw_eyes_5();
  draw_eyes_6();
  draw_eyes_6();
  draw_eyes_7();
  draw_eyes_8();
  display.display();
  delay(100);
  
  /*
  int randNumber = random(300);
  Serial.println(randNumber);

 clear();
  font_size(0.5);
  display.setTextColor(WHITE);
  cursor(0,0);
  draw_rectangle(0, 0, 120, 30,false);
  cursor(15,10);
  draw_text(String(randNumber)+":00:00");
  cursor(0,0);
  draw_text(String(randNumber));
  draw_circle(10,10,5,true);
  draw_triangle(30, 15, 0, 60, 60, 60,true);
  draw_pixel(10,10);
  draw_line(0,0,20,20);
*/

}

void loop() {
  draw();  
}
