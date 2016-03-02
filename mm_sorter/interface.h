#ifndef INTERACE_H
#define INTERFACE_H

#include <msp430.h>
#include <driverlib.h>

#include "colour_struct.h"

void InterfaceInit();
void showNextRGBValue_Debug();
void updateRGBValues_Debug(struct colour detectedColour);
void displayNumberOnLCD(char identifier, int16_t displayNum);
#endif
