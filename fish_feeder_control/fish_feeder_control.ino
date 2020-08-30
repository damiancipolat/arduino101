int LED_1 =13;
int LED_2 =12;
int BUZZER=8;

//Turn on the blinking led.
void feedFishes(){
  digitalWrite(LED_2,HIGH);
  delay(500);
  digitalWrite(LED_2,LOW);
  delay(500);
}

//Turn on the fish OK led.
void fishOK(){
  digitalWrite(LED_1,HIGH);
}

//Sound the alarm.
void feedAlarm(){  
  //Send 500Hz sound signal.
  tone(BUZZER, 500);
  delay(1000);
  
  //Stop sound.
  noTone(BUZZER);
  delay(1000);
}

void setup() {
  pinMode(LED_1,OUTPUT);
  pinMode(LED_2,OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  fishOK();
  feedFishes();
  //feedAlarm();
}
