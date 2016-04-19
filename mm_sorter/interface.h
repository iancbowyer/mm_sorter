#ifndef INTERACE_H
#define INTERFACE_H

#include <msp430.h>
#include <driverlib.h>

#include "hal_LCD.h"
#include "colour_struct.h"
#include "mmCounts.h"

void InterfaceInit();
void showNextCount();
void updateLCDWithCount(struct mmCount count);
void displayNumberOnLCD(char identifier, char identifier2, int16_t displayNum);
#endif
