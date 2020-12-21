// Motor A
int enA = 10; // Pin habilita motor A - PWM
int in1 = 9;  // Pin que controla el sentido de giro
int in2 = 8;  // Pin que controla el sentido de giro

int in4 = 7;  // Pin que controla el sentido de giro
int in3 = 6;  // Pin que controla el sentido de giro
int enB = 5;  // Pin habilita motor B - PWM

void setup ()
{
  Serial.begin (9600);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);  
}

void VelocidadBaja()
{
  analogWrite(enA, 10);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enB, 10);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);  
}

void VelocidadMedia()
{
  analogWrite(enA, 150);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enB, 150);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);  
}

void VelocidadAlta()
{
  analogWrite(enA, 150);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enB, 160);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);  
}

void loop()
{
  /*
  Serial.println("Velocidad baja");
  VelocidadBaja();
  delay(2000);
  Serial.println("Velocidad media");
  VelocidadMedia();
  delay(2000);
  */
  Serial.println("Velocidad alta");
  VelocidadAlta();
  delay(2000);
}
