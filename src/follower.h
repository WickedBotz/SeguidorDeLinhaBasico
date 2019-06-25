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
 * Converte o resultado dos sensores em um número, que será comparado com as constantes
 * dos sensores.
 */
int sensor_array_check(reflectance sensors[]) {
    size_t n = SENSORNO;
    int sensor_check = 0;

    for (int i = 0; i < n; i++) {
        sensor_check = sensor_check | (lowerTreshold(sensors[i]) ? 1 : 0) << (i*8);
    }

    return sensor_check;
}

void follow_line(reflectance sensors[], axis motor_axis) {
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