const int buzzer = 8; //buzzer to arduino pin 9

void setup(){
     pinMode(buzzer, OUTPUT); // Definimos el pin 8 como salida.
}

void loop(){
  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec
}
