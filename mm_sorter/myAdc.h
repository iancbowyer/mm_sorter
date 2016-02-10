#ifndef MYADC_H
#define MYADC_H

#include <msp430.h>
#include <driverlib.h>

void adcInitForSensor();
bool isADCFinished();
int16_t lastConversionValue();
#endif