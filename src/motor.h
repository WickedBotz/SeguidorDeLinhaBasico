#include <Arduino.h>
#include <stdarg.h>

/* Motor *****************************************************/

typedef struct {
  int pwmPin, in1Pin, in2Pin, stdbyPin;
} motor;

motor motorStart(int pwmPin, int in1Pin, int in2Pin, int stdbyPin) {
  motor aux;
  aux.pwmPin = pwmPin;
  aux.in1Pin = in1Pin;
  aux.in2Pin = in2Pin;
  aux.stdbyPin = stdbyPin;

  pinMode(aux.pwmPin, OUTPUT);
  pinMode(aux.in1Pin, OUTPUT);
  pinMode(aux.in2Pin, OUTPUT);
  pinMode(aux.stdbyPin, OUTPUT);

  return aux;
}

void motorCounterClockwise(motor aux, int pwr) {
  analogWrite(aux.pwmPin, pwr);
  digitalWrite(aux.in1Pin, LOW);
  digitalWrite(aux.in2Pin, HIGH);
  digitalWrite(aux.stdbyPin, HIGH);
}

void motorClockwise(motor aux, int pwr) {
  analogWrite(aux.pwmPin, pwr);
  digitalWrite(aux.in1Pin, HIGH);
  digitalWrite(aux.in2Pin, LOW);
  digitalWrite(aux.stdbyPin, HIGH);
}

/* End Motor *****************************************************/

/* Axis **********************************************************/
typedef struct {
  motor motorL, motorR;
  unsigned long beginTime;
} axis;

axis axisStartMotor(motor motorL, motor motorR);

axis axisStartPin(int pwmPinL, int in1PinL, int in2PinL, int stdbyPin, int pwmPinR, int in1PinR, int in2PinR) {
  motor motorL = motorStart(pwmPinL, in1PinL, in2PinL, stdbyPin);
  motor motorR = motorStart(pwmPinR, in1PinR, in2PinR, stdbyPin);

  return axisStartMotor(motorL, motorR);
}

axis axisStartMotor(motor motorL, motor motorR) {
  axis aux;

  aux.motorL = motorL;
  aux.motorR = motorR;

  return aux;
}

void axisForward(axis aux, int leftPwr, int rightPwr) {
  motorCounterClockwise(aux.motorL, leftPwr);
  motorClockwise(aux.motorR, rightPwr);
}

void axisBackward(axis aux, int leftPwr, int rightPwr) {
  motorClockwise(aux.motorL, leftPwr);
  motorCounterClockwise(aux.motorR, rightPwr);
}

void axisRight(axis aux, int leftPwr, int rightPwr) {
  motorCounterClockwise(aux.motorL, leftPwr);
  motorCounterClockwise(aux.motorR, rightPwr);
}

void axisLeft(axis aux, int leftPwr, int rightPwr) {
  motorClockwise(aux.motorL, leftPwr);
  motorClockwise(aux.motorR, rightPwr);
}

void axisMove(axis aux, int leftPwr, int rightPwr) {
  if (leftPwr && rightPwr < 0) { /* mover para trás */
    leftPwr *= -1; rightPwr *= -1;
    axisBackward(aux, leftPwr, rightPwr);
  } else if (leftPwr < 0) { /* mover para a esquerda */
    leftPwr *= -1;
    axisLeft(aux, leftPwr, rightPwr);
  } else if (rightPwr < 0) { /* mover para a direita */
    rightPwr *= -1;
    axisRight(aux, leftPwr, rightPwr);
  } else { /* mover para frente */
    axisForward(aux, leftPwr, rightPwr);
  }
}

/* End Axis **********************************************************************************/


