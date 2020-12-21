#include <SoftwareSerial.h>  // libreria que permite establecer pines digitales.
SoftwareSerial miBT(11, 12); // pin 10 como RX, pin 11 como TX.

String DATO  = "0";//Variable para almacenar caracter recibido

void setup(){
  Serial.begin(9600);    // comunicacion de monitor serial a 9600 bps
  Serial.println("Listo");  // escribe Listo en el monitor
  miBT.begin(38400);        //Comunicacion serie entre Arduino y el modulo a 38400 bps}
}

void loop(){
  
  if (miBT.available()){
    DATO = miBT.readString();
    Serial.println(DATO);
  }
  
}
