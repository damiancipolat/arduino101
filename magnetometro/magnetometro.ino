#include <Wire.h>    // incluye libreria bus I2C
#include <MechaQMC5883.h> // incluye libreria para magnetometro QMC5883L

MechaQMC5883 qmc;   // crea objeto

void setup() {
  Wire.begin();     // inicializa bus I2C
  Serial.begin(9600);   // inicializa monitor serie a 9600 bps
  qmc.init();     // inicializa objeto
}

void loop() {
  int x,y,z;      // variables de los 3 ejes
  float acimut,geografico;  // variables para acimut magnetico y geografico
  float declinacion = -9.13;    // declinacion desde pagina: http://www.magnetic-declination.com/
  qmc.read(&x,&y,&z,&acimut);   // lectura de los ejes y acimut magnetico
  
  geografico = acimut + declinacion;  // acimut geografico como suma del magnetico y declinacion
  if(geografico < 0)      // si es un valor negativo
  geografico = geografico + 360;  // suma 360 y vuelve a asignar a variable

  Serial.print("Acimut geografico: ");  // muestra texto Acimut geografico:
  Serial.print(geografico,0);   // muestra valor de acimut geografico sin decimales
  Serial.println(" grados");    // muestra texto grados

  delay(500);       // demora de 500 mseg.
}
