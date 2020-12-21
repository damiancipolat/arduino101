// Sensor de Humedad    
           
    // Conectamos el sensor de la siguiente forma:       
    // GND    -> GND       
    // VCC    -> 5V       
    // DAT    -> A0           
     

int Valor; 
   
void setup() {
  Serial.begin(9600);
} 
 
void loop(){  
  Serial.print("Sensor de Humedad valor:");  
  Valor = analogRead(0);  
  Serial.print(Valor);  
 
  if (Valor <= 300)  
    Serial.println(" Encharcado");  
  if ((Valor > 300) and (Valor <= 700))  
    Serial.println(" Humedo, no regar");   
  if (Valor > 700)  
    Serial.println(" Seco, necesitas regar");  
  delay(1000); 
} 
