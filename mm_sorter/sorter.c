#include "sorter.h"

void sorterInit()
{}

void moveSorter(enum mmColours detectedMM)
{
  switch (detectedMM)
  {
  case red:
    changeServoADutyCycle(0x60);
  case orange:
    changeServoADutyCycle(0x60);
  case brown:
    changeServoADutyCycle(0x60);
  case green:
    changeServoADutyCycle(0x60);
  case yellow:
    changeServoADutyCycle(0x60);
  case blue: 
    changeServoADutyCycle(0x60);
  }  
  
  
}