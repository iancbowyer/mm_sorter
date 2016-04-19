//MM Sorter
//comparator.c
//Last Modified: 15/04/2016
//updated calibration values
//Author: Ian Bowyer

#include "comparator.h"

struct colour CalibratedColourValues[NUMBER_OF_CATEGORIES];

void comparatorInit()
{
  
}
bool closeToZero(int16_t a)
{
  return (a > -150 && a < 100);
}

enum mmColours decideColour(struct colour sensorReading)
{
  //calculate deltas from absolute values
  int16_t blueDelta = sensorReading.red_value - sensorReading.blue_value;
  int16_t greenDelta = sensorReading.red_value - sensorReading.green_value;
  
  
  //compare deltas against expected vlaues for each MM to determine colour
  if (greenDelta < 150)
  {
    //red or orange
    return red;
  }
  else if(greenDelta < 500 && blueDelta > 50 && blueDelta < 200)
  {
    return brown;
  }
  else if(greenDelta > 480 && blueDelta < 300)
  {
    return green;
  }
  else if(greenDelta < 300 && greenDelta > 200)
  {
    return yellow;
  }
  else if(greenDelta > 400 && blueDelta > 400)
  {
    return blue;
  }
  //if nothing is sensed return empty
  return empty;
}