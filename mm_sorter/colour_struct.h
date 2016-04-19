//MM Sorter
//colour_struct.h
//Last Modified: 28/01/2016
//Added struct for storing sensor readings
//Author: Ian Bowyer

#ifndef COLOUR_STRUCT_H
#define COLOUR_STRUCT_H

#define NUMBER_OF_CATEGORIES 6

#include <msp430.h>
#include <driverlib.h>

//struct to store RGB values generated from ADC
struct colour
{
  int16_t red_value;
  int16_t green_value;
  int16_t blue_value;
};
#endif