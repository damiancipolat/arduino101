//Distance sensor
int trigger = 12;
int eco = 11;

//Engine A, pin constants.
int enA = 10;//señal PWM
int in1 = 9;
int in2 = 8;

//Engine B, pin constants.
int in4 = 7;
int in3 = 6;
int enB = 5;//señal PWM

//Led pins.
int led_front = 3;
int led_back = 4;

void setup (){

  //Set serial mode.
  Serial.begin (9600);

  //Set pin
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //Set distance sensor.
  pinMode(trigger,OUTPUT);
  pinMode(eco,INPUT);

  //Set leds.
  pinMode(led_front,OUTPUT);
  pinMode(led_back,OUTPUT);

}

//Calculate distance.
int getDistance(){
  
  //Send a sound.
  digitalWrite(trigger,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);

  //Read eco.
  int duration=pulseIn(eco,HIGH);
  int distance=(duration/2)/29;

  return distance;

}

//Stop engines.
void engine_stop(){
  
  Serial.println("STOP (!)");
  
  //Engine A
  analogWrite(enA, 150);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  
  //Engine B
  analogWrite(enB, 160);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
}

//Move engine forward.
void forward(){

  Serial.println("Forward (!)");
  
  //Engine A
  analogWrite(enA, 150);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  
  //Engine B
  analogWrite(enB, 160);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

}

//Move engine reverse.
void reverse(){
  
  Serial.println("Reverse (!)");
  
  //Engine A  
  analogWrite(enA, 150);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
  //Engine B
  analogWrite(enB, 160);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
}

//Turn left.
void turn_left(){

  Serial.println("Turn Left (!)");
  
  //Engine A
  analogWrite(enA, 150);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  
  //Engine B
  analogWrite(enB, 160);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
    
}

void loop()
{forward();
  /*
  int distance = getDistance();
  Serial.println((String)distance+"cm");
  digitalWrite(led_front,HIGH);    

  if (distance>=500||distance<=0){
    Serial.println("..............");
    Serial.println("Forward !");    
  }else{
    Serial.print(distance);
    Serial.println("cm");
    digitalWrite(led_back,LOW);
    forward();
  }
  
  if (distance<=10&&distance>=1){
    Serial.println("Alarma.......");
    digitalWrite(led_back,HIGH);    
    reverse();
    delay(1500);
    turn_left();
    delay(500);
    engine_stop();
  }*/

}
