const byte MOTOR_A = 3;  // Motor 2 Interrupt Pin - INT 1 - Right Motor
const byte MOTOR_B = 2;  // Motor 1 Interrupt Pin - INT 0 - Left Motor

// Constant for steps in disk
const float stepcount = 20.00;  // 20 Slots in disk, change if different

// Constant for wheel diameter
const float wheeldiameter = 66.10; // Wheel diameter in millimeters, change if different

// Integers for pulse counters
volatile int counter_A = 0;
volatile int counter_B = 0;

// Motor A
int enA = 10;
int in1 = 9;
int in2 = 8;

// Motor B
int enB = 5;
int in3 = 7;
int in4 = 6;

// Motor A pulse count ISR
void ISR_countA()  
{  Serial.print(counter_A);
  Serial.print(",");
  Serial.print(counter_B);  
  counter_A++;  // increment Motor A counter value
} 

// Motor B pulse count ISR
void ISR_countB()  
{  Serial.print(counter_A);
  Serial.print(",");
  Serial.print(counter_B);  
  counter_B++;  // increment Motor B counter value
}

// Function to convert from centimeters to steps
int CMtoSteps(float cm) {

  int result;  // Final calculation result
  float circumference = (wheeldiameter * 3.14) / 10; // Calculate wheel circumference in cm
  float cm_step = circumference / stepcount;  // CM per Step
  
  float f_result = cm / cm_step;  // Calculate result as a float
  result = (int) f_result; // Convert to an integer (note this is NOT rounded)
  
  return result;  // End and return result

}

// Function to Move Forward
void MoveForward(int steps, int mspeed) 
{
   counter_A = 0;  //  reset counter A to zero
   counter_B = 0;  //  reset counter B to zero
   
   // Set Motor A forward
   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);

   // Set Motor B forward
   digitalWrite(in3, HIGH);
   digitalWrite(in4, LOW);
   
   // Go forward until step value is reached
   while (steps > counter_A && steps > counter_B) {
   
    if (steps > counter_A) {
    analogWrite(enA, mspeed);
    } else {
    analogWrite(enA, 100);
    }
    if (steps > counter_B) {
    analogWrite(enB, mspeed);
    } else {
    analogWrite(enB, 100);
    }
   }
    
  // Stop when done
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero 

}

void setup() 
{
    Serial.begin (9600);       // inicializa el puerto seria a 9600 baudios

  // Attach the Interrupts to their ISR's
  attachInterrupt(digitalPinToInterrupt (MOTOR_A), ISR_countA, RISING);  // Increase counter A when speed sensor pin goes High
  attachInterrupt(digitalPinToInterrupt (MOTOR_B), ISR_countB, RISING);  // Increase counter B when speed sensor pin goes High
} 

void loop()
{
    // Test Motor Movement  - Experiment with your own sequences here.  
  MoveForward(CMtoSteps(100), 255);  // Forward half a metre at 255 speed
  delay(100);
  // Put whatever you want here!  

  Serial.println((int)counter_A+","+(int)counter_B);
  //Serial.print(",");
  //Serial.println(counter_B);
}
