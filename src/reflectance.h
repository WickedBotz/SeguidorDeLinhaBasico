#include <Arduino.h>
#include <stdbool.h>

typedef struct {
  int pin;
  int treshold;
} 
reflectance;


reflectance reflectanceStart(int pin, int treshold){
  reflectance aux; 

  aux.pin = pin;
  aux.treshold = treshold;

  return aux;
} 

int reflectanceRead(reflectance aux){
 // Serial.print("Valor refletancia ");
  long valor = analogRead(aux.pin);
  
 // Serial.println(valor);
  return valor;
}

bool higherTreshold(reflectance aux) {
  return (reflectanceRead(aux) > aux.treshold);
}

bool lowerTreshold(reflectance aux) {
  return (reflectanceRead(aux) < aux.treshold);
}
