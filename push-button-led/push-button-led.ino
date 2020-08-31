// constants won't change. They're used here to set pin numbers:
const int BUTTON_PIN = 7;       // the number of the pushbutton pin

void setup() {
  pinMode(12,OUTPUT);
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // read the state of the switch/button:
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState==0)
     digitalWrite(12,HIGH);
  else
    digitalWrite(12,LOW);

  // print out the button's state 
  Serial.println(buttonState);
}
