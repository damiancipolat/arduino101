#include <LiquidCrystal_I2C.h> //DESCARGAR LIBRERÍA:https://github.com/ELECTROALL/Codigos-arduino/blob/master/LiquidCrystal_I2C.zip
LiquidCrystal_I2C lcd(0x27,12,6); // si no te sale con esta direccion  puedes usar (0x3f,16,2) || (0x27,16,2)  ||(0x20,16,2) 
void setup() {
  lcd.init();
 lcd.backlight();
  lcd.clear();
 lcd.setCursor(0,0);
  lcd.print("==> Hola <=="); 
  lcd.setCursor (0,1);
  lcd.print("==> DAMIAN <");
}
void loop() { 
  lcd.display();
  delay(500);
  lcd.noDisplay();
  delay(500);
}
