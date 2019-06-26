#ifndef __FOLLOWER_H__
#define __FOLLOWER_H__

#include "reflectance.h"
#include "pinning.h"
#include "motor.h"

/* Constantes dos sensores */
#define S111111 077
#define S111110 076
#define S111100 075
#define S111000 070
#define S110000 060
#define S100000 040
#define S011111 037
#define S011110 036
#define S011100 034
#define S011000 030
#define S001111 017
#define S001110 016
#define S001100 014
#define S000111 007
#define S000110 006
#define S000011 003
#define S000001 001
/* Fim constantes dos sensores */

/* Constantes de velocidade */
#define SPEED0 255
#define SPEED1 220
#define SPEED2 200
#define SPEED3 180
#define SPEED4 150
#define SPEED5 100

/**
 * Executa o código do seguidor de linha por máquina de estados
 */
void follow_line(reflectance sensors[], axis motor_axis) {
    int speed_left, speed_right;

    speed_left = speed_right = 0;

    if (
        /* 111111 */
        (lowerTreshold(sensors[0]) && lowerTreshold(sensors[1]) && lowerTreshold(sensors[2]) &&
        lowerTreshold(sensors[3]) && lowerTreshold(sensors[4]) && lowerTreshold(sensors[5])) ||
        /* 011110 */
        (higherTreshold(sensors[0]) && lowerTreshold(sensors[1]) && lowerTreshold(sensors[2]) &&
        lowerTreshold(sensors[3]) && lowerTreshold(sensors[4]) && higherTreshold(sensors[5])) ||
        /* 001100 */
        (higherTreshold(sensors[0]) && higherTreshold(sensors[1]) && lowerTreshold(sensors[2]) &&
        lowerTreshold(sensors[3]) && higherTreshold(sensors[4]) && higherTreshold(sensors[5])) 
    ) { /* ir para frente */
        speed_left = SPEED0;
        speed_right = SPEED0;
    } else /* curva para esquerda */
    if ( /* 111110 */
        (lowerTreshold(sensors[0]) && lowerTreshold(sensors[1]) && lowerTreshold(sensors[2]) &&
        lowerTreshold(sensors[3]) && lowerTreshold(sensors[4]) && higherTreshold(sensors[5]))
    ) {
        speed_left = SPEED0;
        speed_right = SPEED1;
    } else if ( /* 111100 */
        (lowerTreshold(sensors[0]) && lowerTreshold(sensors[1]) && lowerTreshold(sensors[2]) &&
        lowerTreshold(sensors[3]) && higherTreshold(sensors[4]) && higherTreshold(sensors[5]))
    ) {
        speed_left = SPEED0;
        speed_right = SPEED2;
    }

    
    
    
    /* 111000 */
    /* 110000 */
    /* 100000 */

    /* 011100 */
    /* 011000 */
    /* 010000 */   

    /* curva para direita */
    /* 011111 */
    /* 001111 */
    /* 000111 */
    /* 000011 */
    /* 000001 */

    /* 001110 */
    /* 000110 */
    /* 000010 */   

}


/**
 * Converte o resultado dos sensores em um número, que será comparado com as constantes
 * dos sensores.
 */
int sensor_array_check(reflectance sensors[]) {
    size_t n = SENSORNO;
    int sensor_check = 0;

    for (int i = (n-1); i >= 0; i--) {
        sensor_check = sensor_check | (lowerTreshold(sensors[i]) ? 1 : 0) << (i*8);
    }

    return sensor_check;
}

void follow_line_constants(reflectance sensors[], axis motor_axis) {
    int sensor_value  = sensor_array_check(sensors);
    int speed_right, speed_left;

    switch (sensor_value)
    {
    /* Para frente */
    case S111111:
    case S011110:
    case S001100:
        /* code */
        speed_right = SPEED0;
        speed_left = SPEED0;
        break;
    
    /* Saindo para a direita */
    case S111110:
        speed_right = SPEED0;
        speed_left = SPEED1;
        break;
    case S111100:
        speed_right = SPEED0;
        speed_left = SPEED2;
        break;
    case S111000:
        speed_right = SPEED0;
        speed_left = SPEED3;
        break;
    case S110000:
        speed_right = SPEED0;
        speed_left = SPEED4;
        break;
    case S100000:
        speed_right = SPEED0;
        speed_left = SPEED5;
        break;
    case S011100:
        speed_right = SPEED1;
        speed_left = SPEED2;
        break;
    case S011000:
        speed_right = SPEED1;
        speed_left = SPEED3;
        break;

    /* Saindo para a esquerda */
    case S011111:
        speed_left = SPEED0;
        speed_right = SPEED1;
        break;

    case S001111:
        speed_left = SPEED0;
        speed_right = SPEED2;
        break;

    case S000111:
        speed_left = SPEED0;
        speed_right = SPEED3;
        break;

    case S000011:
        speed_left = SPEED0;
        speed_right = SPEED4;
        break;

    case S000001:
        speed_left = SPEED0;
        speed_right = SPEED5;
        break;
    
    case S001110:
        speed_left = SPEED1;
        speed_right = SPEED2;
        break;

    case S000110:
        speed_left = SPEED1;
        speed_right = SPEED3;
        break;

    default: /* Nenhum desses, pare! */
        speed_left = 0;
        speed_right = 0;
        break;
    }

    axisForward(motor_axis, speed_left, speed_right);
} 

#endif