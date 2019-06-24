#include <Arduino.h>
#include "pinning.h"
#include "reflectance.h"
#include "motor.h"
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(BLUETOOTH_RX, BLUETOOTH_TX);

reflectance sensors[SENSORNO];
axis motorAxis;

void setup() 
{
    Serial.begin(9600); /* Inicializa monitor serial */
    bluetooth.begin(9600);
    
    /* Inicializa sensores de refletância */
    sensors[0] = reflectanceStart(SENSOR1, BLACK);
    sensors[1] = reflectanceStart(SENSOR2, BLACK);
    sensors[2] = reflectanceStart(SENSOR3, BLACK);
    sensors[3] = reflectanceStart(SENSOR4, BLACK);
    sensors[4] = reflectanceStart(SENSOR5, BLACK);
    sensors[5] = reflectanceStart(SENSOR6, BLACK);
    /* Fim sensores */

    /* Inicializa motores */
    motorAxis = axisStartPin(LEFT_PWM, LEFT_IN1, LEFT_IN2, STBY, RIGHT_PWM, RIGHT_IN1, RIGHT_IN2);

}

void loop() 
{
   if (bluetooth.available()) {
        char value = bluetooth.read();
        Serial.println(value);
    }
}

void parse_bluetooth(char option) {
    switch(option) {
        
    }
}