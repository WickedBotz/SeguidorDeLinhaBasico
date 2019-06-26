#include <Arduino.h>
#include "pinning.h"
#include "reflectance.h"
#include "motor.h"
#include <SoftwareSerial.h>
#include "follower.h"

/* Quanto tempo em ms o seguidor irá andar? */
#define STOP_TIME 25000

/* Componentes do Seguidor de Linha */
SoftwareSerial bluetooth(BLUETOOTH_RX, BLUETOOTH_TX);
reflectance sensors[SENSORNO];
axis motorAxis;

void parse_bluetooth(char option);


void setup() 
{
    Serial.begin(9600); /* Inicializa monitor serial */
    bluetooth.begin(9600); /* Inicializa bluetooth */
    
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
    /* Checa entrada vinda do bluetooth */
   if (bluetooth.available()) {
        char value = bluetooth.read();
        parse_bluetooth(value);
    }
}

void parse_bluetooth(char option) {
    switch(option) {
        case '8':
            /* Para frente */
            axisForward(motorAxis, 255, 255);
            break;
        case '4':
            /* Para esquerda */
            axisLeft(motorAxis, 255, 255);
            break;
        case '2':
            /* Para tras */
            axisBackward(motorAxis, 255, 255);
            break;
        case '6':
            /* Para direita */
            axisRight(motorAxis, 255, 255);
            break;
        case 'a':
        case 'x':
            /* Começa o seguidor */
            unsigned long start_time = millis();
            while ((millis() - start_time) < STOP_TIME) {
                follow_line(sensors, motorAxis);
            }
            axisMove(motorAxis, 0, 0); /* Para o robô */

            break;
        default:
            axisForward(motorAxis, 0, 0);
            break;
    }
}