#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,12,6);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() { 
  //Show
  lcd.display();
  delay(500);

  //Write
  lcd.setCursor(0,0);
  lcd.print("Hola !!!!"); 
  lcd.setCursor (0,1);
  lcd.print("Dami y Fran :D");

  //Hidden    
  lcd.noDisplay();
  delay(500);
}
