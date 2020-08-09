//This code is to use with L298n Dual H-bridge motor driver

//It just turns on a DC motor for a certain time and turn it off

//refer to surtrtech.blogspot.com for more information


int in1 = 4;
int in2 = 5;

int in3 = 9;
int in4 = 8;



void setup() {

  //Motor 1
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  //Motor 2
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}

void TurnMotorA(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void TurnMotorB(){
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void TurnOFFA(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void TurnOFFB(){
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


void loop() {

  TurnMotorA();
  delay(1);

  TurnMotorB();
  delay(1);
  
  //TurnOFFA();
  //delay(1);

}
