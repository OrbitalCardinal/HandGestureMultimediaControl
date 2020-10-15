#include "SR04.h"

#define TRIG_PIN 12
#define ECHO_PIN 11 
#define TRIG_PIN2 7
#define ECHO_PIN2 6

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
SR04 sr04_2 = SR04(TRIG_PIN2,ECHO_PIN2);
long a;
long a2;
int minDist = 12;
int secs = 300;

int pauseSecs = 2000;
int pauseDist = 20;
int led = 5;
int button = 4;
bool toggle = false;

void setup() {
   Serial.begin(9600);
   pinMode(led,OUTPUT);
   pinMode(button,INPUT);
   delay(1000);
}

void loop() {
   a=sr04.Distance(); // Tomar distancia inicial sensor derecha
   a2=sr04_2.Distance(); // Tomar distancia inicial sensor izquierda
   if(toggle){ // Comprobar modo - true para power point 
    digitalWrite(led,HIGH);
     if(a < minDist) { // Mano sobre sensor derecho
      Serial.println("Next"); // Enviar Next
      delay(secs);
     } else if(a2 < minDist) { // Mano sobre sensor derecho
      Serial.println("Back"); // Enviar Back
      delay(secs);      
     }
   } else { // - false para video VLC
    digitalWrite(led,LOW);
    if(a > minDist && a < pauseDist && a2 > minDist && a2 < pauseDist ) { // Ambas manos sobre los dos sensores
      Serial.println("Play/Pause");
      delay(pauseSecs);     
    } else {
       if(a < minDist) { // Mano derecha sobre sensor
        delay(2000);
        a=sr04.Distance(); //Tomar distancia de nuevo
        if(a > minDist) { // Si la mano se alejo o quito
          while(true) { 
            a=sr04.Distance();  // Calcular distancia entre cada iteracion
            Serial.println("VUP"); // Enviar VUP (Volume Up - Subir volumen) en cada iteracion
            if(a < minDist) { // Si la mano se acerco al sensor
              break; // Romper el ciclo
            }
            delay(500);
          }
        } else { // Si la mano se quedo cerca del sensor
          while(true) {
            a=sr04.Distance(); // Calcular distancia entre cada iteracion
            Serial.println("Next");   // Envair Next para adelantar
            if(a > minDist) { // Si la mano se quito o alejo
              break;  // Romper con el ciclo
            }
            delay(500);
          }
           
        }
        delay(3000);
       } else if(a2 < minDist) { // Mano izquierda sobre el sensor
        //Misma logica que con mano derecha
        delay(2000);
        a2=sr04_2.Distance();
        if(a2 > minDist) {
          while(true) {
            a2=sr04_2.Distance();
            Serial.println("VDN");
            if(a2 < minDist) {
              break;
            }
            delay(500);
          }
        } else {
          while(true) {
            a2=sr04_2.Distance();
            Serial.println("Back");
            if(a2 > minDist) {
              break;
            }
            delay(500);
          }
        }
        delay(3000);      
       }
    }

   }
   
   if(digitalRead(button) == HIGH) { // Si se presiona boton cambiar de modo
       toggle = !toggle;
//       delay(500);
   } 
}
