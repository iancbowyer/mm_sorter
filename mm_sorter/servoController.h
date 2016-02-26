#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H
#include <msp430.h>
#include <driverlib.h>



void seperatorInit();
void changeServoADutyCycle(int16_t pulseWidth);
void changeServoBDutyCycle(int16_t pulseWidth);
void switchServo(bool servo);
#endif