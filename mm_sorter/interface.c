//MM Sorter
//main.c
//Last Modified: 18/04/2016
//Enabled 2 digit identifier to differentiate Br(Brown) for Bl(Blue)
//Author: Ian Bowyer

#include "interface.h"

#include "mm_colour_enum.h"

enum mmColours colours;

void displayNumberOnLCD(char identifier, char identifier2, int16_t displayNum);

void InterfaceInit()
{
  //reset and clear LCD screen
  clearLCD();
  Init_LCD();
}

void showNextCount()
{
  //increment enumerated type
  //reset when reaching last value
  if (colours == blue)
  {
    colours = red;
  }
  else
  {
    colours++;
  }
}

void updateLCDWithCount(struct mmCount count)
{  
  //depending on current UI state display relevant count adn an identifieer on the screen
  switch(colours)
  {
  case red: 
    displayNumberOnLCD('R','E', count.red);
    break;
  case orange: 
    displayNumberOnLCD('O', 'R', count.orange);
    break;
  case brown: 
    displayNumberOnLCD('B', 'R',count.brown);
    break;
  case green: 
    displayNumberOnLCD('G', 'R',count.green);
    break;
  case yellow:
    displayNumberOnLCD('Y', 'E', count.yellow);
    break;
  case blue:
    displayNumberOnLCD('B', 'L',count.blue);
    break;
  } 
}

void displayNumberOnLCD(char identifier, char identifier2, int16_t displayNum)
{
  //display 2 digit identifier
  showChar(identifier, pos1);
  showChar(identifier2, pos2);
  //seperate number into 3 digits and display
  showChar((((displayNum /100) % 10) + 48), pos4);
  showChar((((displayNum /10) % 10) + 48), pos5);
  showChar(((displayNum % 10) + 48), pos6);
}