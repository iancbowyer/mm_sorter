#include "comparator.h"

struct colour CalibratedColourValues[NUMBER_OF_CATEGORIES];

void comparatorInit()
{
  //red
  CalibratedColourValues[0].red_value = 0;
  CalibratedColourValues[0].green_value = 0;
  CalibratedColourValues[0].blue_value = 0;
  
  //orange
  CalibratedColourValues[1].red_value = 0;
  CalibratedColourValues[1].green_value = 0;
  CalibratedColourValues[1].blue_value = 0;
  
  //brown
  CalibratedColourValues[2].red_value = 0;
  CalibratedColourValues[2].green_value = 0;
  CalibratedColourValues[2].blue_value = 0;
  
  //green
  CalibratedColourValues[3].red_value = 0;
  CalibratedColourValues[3].green_value = 0;
  CalibratedColourValues[3].blue_value = 0;
  
  //yellow
  CalibratedColourValues[4].red_value = 0;
  CalibratedColourValues[4].green_value = 0;
  CalibratedColourValues[4].blue_value = 0;
  
  //blue
  CalibratedColourValues[5].red_value = 0;
  CalibratedColourValues[5].green_value = 0;
  CalibratedColourValues[5].blue_value = 0;
}

enum mmColours decideColour(struct colour SensorReading)
{
  //todo add comparison for this
  //just return red for now
  return red;
}