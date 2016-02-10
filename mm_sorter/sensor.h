/*******************************
Sensor code will initialise and run all aspects of sensor hardware:
Enabling each LED in turn and reading from LDR
Converting LDR voltage to digital signal
Creating colour struct
Reporting colour back to main
*******************************/

#ifndef SENSOR_H
#define SENSOR_H

#include <msp430.h>
#include <driverlib.h>

#include "colour_struct.h"

#define RED_LED_PORT  GPIO_PORT_P5
#define RED_LED_PIN GPIO_PIN1

#define GREEN_LED_PORT  GPIO_PORT_P5
#define GREEN_LED_PIN GPIO_PIN2

#define BLUE_LED_PORT  GPIO_PORT_P5
#define BLUE_LED_PIN GPIO_PIN3

//time to keep LED on for before reading from LDR
//led warmup time + LDR settle time + buffer
#define LED_DELAY 100000

int16_t getLDRVoltageForLED(uint8_t selectedPort, uint16_t selectedPins);
void sensorInit();
struct colour runSensor();

#endif