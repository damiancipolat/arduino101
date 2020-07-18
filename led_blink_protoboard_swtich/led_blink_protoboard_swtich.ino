//Pin 2: Input for reading the button
//Pin 3: Output for controlling the led
int ButtonValue = 0;
int Button = 4;
int LED=2;

void setup() {
  Serial.begin(9600);
  pinMode(Button, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  ButtonValue = digitalRead(Button);

  if(ButtonValue!=0){
   digitalWrite(LED,HIGH);
   Serial.println("LED ON!!!");
  }else{
   digitalWrite(LED,LOW); 
   Serial.println("LED OF!!!");
  }
  
}
