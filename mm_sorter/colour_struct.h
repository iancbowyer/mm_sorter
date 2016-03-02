#ifndef COLOUR_STRUCT_H
#define COLOUR_STRUCT_H

#define NUMBER_OF_CATEGORIES 6

#include <msp430.h>
#include <driverlib.h>

struct colour
{
  int16_t red_value;
  int16_t green_value;
  int16_t blue_value;
};
#endif