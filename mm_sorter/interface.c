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
  if (colours == b)
  {
    colours = r;
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
  case r: 
    displayNumberOnLCD('R', detectedColour.red_value);
    break;
  case g:
    displayNumberOnLCD('G', detectedColour.green_value);
    break;
  case b:
    displayNumberOnLCD('B', detectedColour.blue_value);
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