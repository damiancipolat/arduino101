void setup(){
  //Set pin 13 in output mode
  pinMode(13,OUTPUT);
}

void loop(){
  //Turn ON the led.
  digitalWrite(13,HIGH);
  
  //Make a delay in ms 1seg.
  delay(1000);
  
  //Turn OFF the led.
  digitalWrite(13,LOW);
  
  //Make a delay in ms 1seg.
  delay(1000);
}
