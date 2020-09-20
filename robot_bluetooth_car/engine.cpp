#include "engine.h"
#include "Arduino.h"

//Create the engine.
robo_engine defineEngine(char dir,int p1, int p2){
  robo_engine tmpEngine;
  
  //Set values. 
  tmpEngine.direction=dir;
  tmpEngine.pin_1=p1;
  tmpEngine.pin_2=p2;
  tmpEngine.active=false;

  return tmpEngine; 
}

//Go forward.
void goForward(robo_engine engine){
  digitalWrite(engine.pin_1, HIGH);
  digitalWrite(engine.pin_2, LOW);
}

//Go reverse.
void goReverse(robo_engine engine){
  digitalWrite(engine.pin_1, LOW);
  digitalWrite(engine.pin_2, HIGH);
}

//Stop!.
void stopEngine(robo_engine engine){
  digitalWrite(engine.pin_1, LOW);
  digitalWrite(engine.pin_2, LOW);
}

//Run the engine by the configuration.
bool runEngine(robo_engine engine){
  
  //Desactive engine.
  if (!(engine.active)){    
    stopEngine(engine);
    return false;
  }

  //Handle direction.
  switch(engine.direction){
    case 'F':
      goForward(engine);
      break;
    case 'R':
      goReverse(engine);
      break;
  }
  
}
