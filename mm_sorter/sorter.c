//MM Sorter
//main.c
//Last Modified: 18/04/2016
//Updated container positions, changed servo rotation
//Author: Ian Bowyer

#include "sorter.h"

void sorterInit()
{}

void moveSorter(enum mmColours detectedMM)
{
  //rotate sorter servo motor to calibrated rotary position bases on detected MM
  //total range of 0x60 to 0x20
  switch (detectedMM)
  {
  case red:
    changeServoBDutyCycle(0x56);
    break;
  case orange:
    changeServoBDutyCycle(0x50);
    break;
  case brown:
    changeServoBDutyCycle(0x44);
    break;
  case green:
    changeServoBDutyCycle(0x3A);
    break;
  case yellow:
    changeServoBDutyCycle(0x32);
    break;
  case blue: 
    changeServoBDutyCycle(0x2B);
    break;
  }  
  
  
}