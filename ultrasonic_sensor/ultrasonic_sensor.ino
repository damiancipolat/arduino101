int TRIG = 10;
int ECO = 9;
int LED =13;
int duration;
int distance;

void setup() {
  pinMode(TRIG,OUTPUT);
  pinMode(ECO,INPUT);
  pinMode(LED,INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);
  
  duration=pulseIn(ECO,HIGH);
  distance=(duration/2)/29;

  if (distance>=500||distance<=0){
    Serial.println("..............");
  }else{
    Serial.print(distancia);
    Serial.println("cm");
    digitalWrite(LED,LOW);    
  }
  
  if (distance<=10&&distance>=1){    
    digitalWrite(LED,HIGH);
    Serial.println("Alarma.......");
  }
  delay(400);
}
