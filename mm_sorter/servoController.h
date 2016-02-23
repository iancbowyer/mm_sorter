#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H
#include <msp430.h>
#include <driverlib.h>

void seperatorInit();
void changeDutyCycle(int16_t pulseWidth);
#endif