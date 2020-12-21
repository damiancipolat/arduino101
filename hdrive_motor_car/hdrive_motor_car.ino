//Motor A
int sensor_1=4; //Sensor 1
int enA = 10;   //Pin habilita motor B - PWM
int in1 = 9;    //Pin que controla el sentido de giro
int in2 = 8;    //Pin que controla el sentido de giro

//Motor B
int sensor_2=3; //Sensor 2
int in3 = 7;    //Pin que controla el sentido de giro
int in4 = 6;    //Pin que controla el sentido de giro
int enB = 5;    //Pin habilita motor B - PWM

//Steps - counter.
int steps_1=0;
int steps_2=0;

//Constant for steps in disk
const float stepcount = 20;
 
//Constant for wheel diameter
const float wheeldiameter = 66.10;

//Integers for pulse counters
volatile int counter_A = 0;
volatile int counter_B = 0;

//Function to convert from centimeters to steps
int CMtoSteps(float cm) { 
  int result;  
  float circumference = (wheeldiameter * 3.14)/10;
  float cm_step = circumference/stepcount;  
  float f_result = cm/cm_step;  
  result = (int)f_result;

  return result;   
}

//Engine A
void motorA(){
  analogWrite(enA, 200);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
}

//Engine B
void motorB(){
  analogWrite(enB, 255);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);  
}

// Function to Move Forward
void MoveForward(int steps, int mspeed) 
{
   counter_A = 0;//reset counter A to zero.
   counter_B = 0;//reset counter B to zero.
   
   //Set Motor A forward
   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);
 
   //Set Motor B forward
   digitalWrite(in3, HIGH);
   digitalWrite(in4, LOW);
   
   //Go forward until step value is reached
   while (steps > counter_A && steps > counter_B) {
  
    if (steps > counter_A) {
      analogWrite(enA, mspeed);
    } else {
      analogWrite(enA, 0);
    }
    
    if (steps > counter_B) {
      analogWrite(enB, mspeed);
    } else {
      analogWrite(enB, 0);
    }
    
   }
    
  //Stop when done
  analogWrite(enA, 0);
  analogWrite(enB, 0);

  //Reset values.
  counter_A = 0;
  counter_B = 0;
 
}

// Motor A pulse count ISR
void ISR_countA()  
{
  counter_A++;  // increment Motor A counter value
} 
 
// Motor B pulse count ISR
void ISR_countB()  
{
  counter_B++;  // increment Motor B counter value
}

void setup()
{
  Serial.begin (9600);

  //Motor 1
  pinMode(sensor_1,INPUT_PULLUP);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  //Motor 2
  pinMode(sensor_2,INPUT_PULLUP);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);  

  attachInterrupt(digitalPinToInterrupt(sensor_1), ISR_countA, RISING);
  attachInterrupt(digitalPinToInterrupt(sensor_2), ISR_countB, RISING);
  
  MoveForward(CMtoSteps(50),255);
}

void loop()
{
  /*
  //Steps
  if(digitalRead(sensor_1))
    counter_A=counter_A+1;

  if(digitalRead(sensor_2))
    counter_B=counter_B+1;
    
  MoveForward(CMtoSteps(50), 255);
  delay(1000);*/
  
/*
  Serial.println("Velocidad X");
  Velocidad();* 
  if (steps_1>=steps_2)
    motorA();
  else
    motorB();
*/


  
  //Salida
  //Serial.println("Step 1:"+(String)steps_1);
  //Serial.println("Step 2:"+(String)steps_2);  
  //Serial.println("M1");
  //Serial.println("M2");  
  //delay(2000);
}
