#include <Keypad.h>

const byte FILAS = 4;
const byte COLUMNAS = 4;
int LED = 13;

char keys[FILAS][COLUMNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinesFilas[FILAS] = {9,8,7,6};
byte pinesColumnas[COLUMNAS] = {5,4,3,2};

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

// almacena la tecla presionada
char TECLA;

// almacena en un array 6 digitos ingresados
char CLAVE[7];

void setup()
{
 // inicializa comunicacion serie
 Serial.begin(9600);

 // Activo led
 pinMode(13,OUTPUT);
 
}

void loop(){
  
  TECLA = teclado.getKey();
  digitalWrite(13,LOW);
  
  if (TECLA){
    digitalWrite(13,HIGH);
    Serial.println(TECLA);
  }
}
