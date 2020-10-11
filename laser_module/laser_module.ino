int LASER=10;

void setup(){
  pinMode(LASER, OUTPUT);
  digitalWrite(LASER, LOW);
}

void loop(){
  digitalWrite(LASER, HIGH);
}
