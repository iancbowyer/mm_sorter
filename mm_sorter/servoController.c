//MM Sorter
//main.c
//Last Modified: 18/03/2016
//Added support for second servo motor
//Author: Ian Bowyer

#include "servoController.h"

void servoInit()
{
  //set emux control pin as output
  //GPIO setup
  P1DIR |= GPIO_PIN7 | GPIO_PIN6;
  P1SEL0 |= GPIO_PIN7 | GPIO_PIN6;
  
  //timer setup
  //enable 32KHz up counter
  TA0CCR0|= 0x280;
  //initialise 2 1ms period up counters
  TA0CCR1 |= 0x20;
  TA0CCR2 |= 0x20;
  
  //set timer outputs 1 and 2 to reset/set mode
  //creates PWM using TA0CCR0 and TA0CCR1 for first output
  //and TA0CCR0 and TA0CCR2 for second output
  TA0CCTL1 |= OUTMOD_7;
  TA0CCTL2 |= OUTMOD_7;
  
  //start counting
  TA0CTL |= TASSEL_1 + MC_1;
}

void changeServoADutyCycle(int16_t pulseWidth)
{
  //modify servo A duty cycle
  TA0CCR1 = pulseWidth;
}

void changeServoBDutyCycle(int16_t pulseWidth)
{
  //modify servo B duty cycle
  TA0CCR2 = pulseWidth;
}