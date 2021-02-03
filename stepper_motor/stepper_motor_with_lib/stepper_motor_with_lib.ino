//http://manueldelgadocrespo.blogspot.com/p/biblioteca-steeppr.html
#include <Stepper.h> // incluye libreria stepper
 
Stepper motor1(2048, 8, 10, 9, 11);   // pasos completos

//2048 -> total de pasos de un giro completo.
//1024 -> la mitad
//512 -> 1/4

void setup() {
  Serial.begin(9600);
  motor1.setSpeed(10);       // en RPM (valores de 1, 2 o 3 para 28BYJ-48)
}
 
void loop() {
  Serial.println("Paso !");
  motor1.step(512);         // cantidad de pasos
  delay(2000);        // demora de 2 seg. por cuestiones practicas
 // motor1.step(-512);         // cantidad de pasos
  //delay(2000);        // demora de 2 seg. por cuestiones practicas  
}
