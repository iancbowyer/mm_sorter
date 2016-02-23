#include "servoController.h"

void seperatorInit()
{
  //GPIO setup
  P1DIR |= GPIO_PIN7;
  P1SEL0 |= GPIO_PIN7;
  
  //timer setup
  TA0CCR0|= 0x280;
  TA0CCR1 |= 0x20;
  TA0CCTL1 |= OUTMOD_7;
  TA0CTL |= TASSEL_1 + MC_1;
}

void changeDutyCycle(int16_t pulseWidth)
{
  TA0CCR1 = pulseWidth;
}