#include <SoftwareSerial.h>  // libreria que permite establecer pines digitales.
SoftwareSerial miBT(10, 11); // pin 10 como RX, pin 11 como TX.

String DATO  = "0";//Variable para almacenar caracter recibido
int LEDROJO  = 2;//LED rojo a pin digital numero 2
int LEDVERDE = 3;//LED verde a pin digital numero 3

void setup(){
  Serial.begin(9600);    // comunicacion de monitor serial a 9600 bps
  Serial.println("Listo");  // escribe Listo en el monitor
  miBT.begin(38400);        //Comunicacion serie entre Arduino y el modulo a 38400 bps
  pinMode(LEDROJO, OUTPUT); //Pin 2 como salida
  pinMode(LEDVERDE, OUTPUT);//Pin 3 como salida
}

void loop(){
  
  if (miBT.available()){
    DATO = miBT.readString();
    Serial.println(DATO);
    
    if(DATO=="1")
      digitalWrite(LEDROJO, !digitalRead(LEDROJO));

    if(DATO=="2")
      digitalWrite(LEDVERDE, !digitalRead(LEDVERDE));

  }
  
}
