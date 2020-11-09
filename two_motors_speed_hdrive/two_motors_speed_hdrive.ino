/* 
 Ejemplo de Control de Motores DC con el modulo L298N
 Creado EL 09/05/17 para PROYECTOSCONARDUINO.COM
*/

// Motor A
int enA = 10;  // Pin habilita motor B - PWM
int in1 = 9;  // Pin que controla el sentido de giro
int in2 = 8;  // Pin que controla el sentido de giro

// Motor B
int enB = 5;  // Pin habilita motor B - PWM
int in3 = 7;  // Pin que controla el sentido de giro
int in4 = 6;  // Pin que controla el sentido de giro

void setup () 
{
  // Configura todos los pines como salida
  pinMode(enB, OUTPUT);
  pinMode(enA, OUTPUT);  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void VelocidadFija()
{
  // Gira el Motor A en ambas direcciones a una velocidad fija
  // Gira el motor A en sentido horario
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(3000); // Giramos los motores por 3 segundos

  // Detenemos el Motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW); 
}

void VelocidadVariable()
{
  // Giramos el Motor B en un rango de velocidad
  // Usamos PWM para enviar analogWrite() y controlar la maxima velocidad posible
  
  // Giramos los motores en un sentido
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  // Aceleramos desde 0 hasta la velocidad maxima
  for(int i = 0; i < 255; i++)
  {
    analogWrite(enA, i); // Usamos PWM para variar la velocidad
    analogWrite(enB, i); // Usamos PWM para variar la velocidad
    Serial.print("Velocidad: ");
    Serial.println(i);
    delay(20);
  }

  // Desaceleramos desde la velocidad maxima hasta llegar a 0 
  for(int i = 255; i > 0; i--)
  {
    analogWrite(enA, i); // Usamos PWM para variar la velocidad
    analogWrite(enB, i); // Usamos PWM para variar la velocidad
    Serial.print("Velocidad: ");
    Serial.println(i);
    delay(20);
  }

  // Detenemos los motores
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


void loop()
{
  Serial.begin (9600);       // inicializa el puerto seria a 9600 baudios
  VelocidadFija();
  Serial.println("Inicia Prueba de Velocidad Fija");
  delay(2000);
  VelocidadVariable();
  Serial.println("Inicia Prueba de Velocidad Variable");
  delay(2000);
}
