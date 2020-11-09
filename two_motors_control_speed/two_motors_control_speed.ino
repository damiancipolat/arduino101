// Motor A
int enA = 9;  // Pin habilita motor B - PWM
int in1 = 7;  // Pin que controla el sentido de giro
int in2 = 6;  // Pin que controla el sentido de giro

void setup ()
{
  Serial.begin (9600);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void VelocidadBaja()
{
  analogWrite(enA, 50);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void VelocidadMedia()
{
  analogWrite(enA, 150);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void VelocidadAlta()
{
  analogWrite(enA, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void loop()
{
  Serial.println("Velocidad baja");
  VelocidadBaja();
  delay(1000);
  Serial.println("Velocidad media");
  VelocidadMedia();
  delay(1000);
  Serial.println("Velocidad alta");
  VelocidadAlta();
  delay(1000);
}
