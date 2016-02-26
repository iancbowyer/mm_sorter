#include "servoController.h"

void seperatorInit()
{
  //set emux control pin as output
  GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN6);
  //GPIO setup
  P1DIR |= GPIO_PIN7 | GPIO_PIN6;
  P1SEL0 |= GPIO_PIN7 | GPIO_PIN6;
  
  //timer setup
  TA0CCR0|= 0x280;
  TA0CCR1 |= 0x20;
  TA0CCR2 |= 0x20;
  TA0CCTL1 |= OUTMOD_7;
  TA0CCTL2 |= OUTMOD_7;
  TA0CTL |= TASSEL_1 + MC_1;
}

void changeServoADutyCycle(int16_t pulseWidth)
{
  TA0CCR1 = pulseWidth;
}

void changeServoBDutyCycle(int16_t pulseWidth)
{
  TA0CCR2 = pulseWidth;
}