#include "engine.h"
#include <SoftwareSerial.h>  // libreria que permite establecer pines digitales.
SoftwareSerial miBT(10, 11); // pin 10 como RX, pin 11 como TX.
String DATO  = "0";//Variable para almacenar caracter recibido

//Define engine representation.
robo_engine leftEngine = defineEngine('F',2,3); 
robo_engine rigthEngine = defineEngine('F',9,8);

void setup() {
  Serial.begin(9600);
  Serial.println("Listo");
  miBT.begin(38400);
  
  //Left motor.
  pinMode(leftEngine.pin_1, OUTPUT);
  pinMode(leftEngine.pin_2, OUTPUT);

  //Rigth motor.
  pinMode(rigthEngine.pin_1, OUTPUT);
  pinMode(rigthEngine.pin_2, OUTPUT);

  //Start engines.
  leftEngine.active=false;
  rigthEngine.active=false;
}

void loop() {

  //Serial.println(leftEngine.direction);
 // Serial.println(rigthEngine.direction);
  
  if (miBT.available()){
    DATO = miBT.readString();
    Serial.println(DATO);

    if (DATO=="3"){
      leftEngine.active=!leftEngine.active;
      rigthEngine.active=!rigthEngine.active;
    }

    if (DATO=="1"){
      leftEngine.direction='F';
      rigthEngine.direction='F';
    }
    
    if (DATO=="2"){
      leftEngine.direction='R';
      rigthEngine.direction='R';
    }
    
  }

  runEngine(leftEngine);
  runEngine(rigthEngine);
 
}
