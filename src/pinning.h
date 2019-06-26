#ifndef __PINNING_H__
#define __PINNING_H__

#include <Arduino.h>

/**
 * Pinagem dos componentes
 */

/* Portas sensor QTR */
#define SENSOR1 A0
#define SENSOR2 A1
#define SENSOR3 A2
#define SENSOR4 A3
#define SENSOR5 A6
#define SENSOR6 A7

/* Número de sensores */
#define SENSORNO 6

/* Limite de preto */
#define BLACK 800

/* Portas dos motores */

/* Motor direito */
#define RIGHT_PWM 9
#define RIGHT_IN2 7
#define RIGHT_IN1 8

#define STBY 6 /* habilita a locomoção */

/* Motor esquerdo */
#define LEFT_IN1 4
#define LEFT_IN2 5
#define LEFT_PWM 3

/* ********************** */
/* Portas bluetooth */
#define BLUETOOTH_TX 10
#define BLUETOOTH_RX 11

#endif