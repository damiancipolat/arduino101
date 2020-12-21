int sensor_1 = 5;

int steps_1=0;

void setup() {
  Serial.begin(9600);
  pinMode(sensor_1,INPUT_PULLUP);
  Serial.println("OK");
}

void loop() {

    
   if(digitalRead(sensor_1))
    steps_1=steps_1+1;

 

  Serial.println("Step 1:"+(String)steps_1);
  
}
