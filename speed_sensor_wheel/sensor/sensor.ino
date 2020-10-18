int sensor = 11;
unsigned long start_time = 0;
unsigned long end_time = 0;
int steps=0;
float steps_old=0;
float temp=0;
float rps=0;

void setup() {
  Serial.begin(9600);
  pinMode(sensor,INPUT_PULLUP);
  Serial.println("OK");
}

void loop() {

   if(digitalRead(sensor))
    steps=steps+1;
  
  temp=steps-steps_old;
  steps_old=steps;
  rps=(temp/20);

  Serial.println("Step:"+(String)steps+" - RPM:"+(String)rps);
  
}
