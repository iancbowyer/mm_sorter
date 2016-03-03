#include "sorter.h"

void sorterInit()
{}

void moveSorter(enum mmColours detectedMM)
{
  switch (detectedMM)
  {
  case red:
    changeServoBDutyCycle(0x60);
    break;
  case orange:
    changeServoBDutyCycle(0x54);
    break;
  case brown:
    changeServoBDutyCycle(0x48);
    break;
  case green:
    changeServoBDutyCycle(0x42);
    break;
  case yellow:
    changeServoBDutyCycle(0x36);
    break;
  case blue: 
    changeServoBDutyCycle(0x30);
    break;
  }  
  
  
}