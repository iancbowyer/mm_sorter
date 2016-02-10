#include "interface.h"
#include "hal_LCD.h"
#include "rgb_enum.h"

enum RGB colours;

void displayNumberOnLCD(char identifier, int16_t displayNum);

void InterfaceInit()
{
  Init_LCD();
}

void showNextRGBValue_Debug()
{
  if (colours == blue)
  {
    colours = red;
  }
  else
  {
    colours++;
  }
}

void updateRGBValues_Debug(struct colour detectedColour)
{  
  switch(colours)
  {
  case red:
    displayNumberOnLCD('R', detectedColour.red);
    break;
  case green:
    displayNumberOnLCD('G', detectedColour.green);
    break;
  case blue:
    displayNumberOnLCD('B', detectedColour.blue);
    break;        
  }
}

void displayNumberOnLCD(char identifier, int16_t displayNum)
{
  showChar(identifier, pos1);
  showChar((((displayNum /1000) % 10) + 48), pos3);
  showChar((((displayNum /100) % 10) + 48), pos4);
  showChar((((displayNum /10) % 10) + 48), pos5);
  showChar(((displayNum % 10) + 48), pos6);
}