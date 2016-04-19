//MM Sorter
//myAdc.c
//Last Modified: 8/04/2016
//Switched ADC input pin from onbard potentiometer (8.1) to LDR (1.5) 
//Author: Ian Bowyer

#include "myAdc.h"
#include "interface.h"
int16_t adcValue;
bool adcFinished= false;

// ADC interrupt service routine
#pragma vector=ADC_VECTOR           // these two lines are used by IAR and CCC
__interrupt void ADC_ISR(void)
{
  switch(__even_in_range(ADCIV,ADCIV_ADCIFG))
  {
    case ADCIV_ADCIFG:              // conversion complete
        ADC_clearInterrupt(__MSP430_BASEADDRESS_ADC__,ADC_COMPLETED_INTERRUPT_FLAG);
        adcValue = ADC_getResults(__MSP430_BASEADDRESS_ADC__);
        adcFinished = true;
        //displayNumberOnLCD('C', adcValue);
        //ADC_startConversion(__MSP430_BASEADDRESS_ADC__,ADC_SINGLECHANNEL);
    break;
  }
}

void adcInitForSensor()
{
  //configure pin 1.5
  GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION);
  
  //setup ADC to take value from 1.5 and convert to binary
  //converts one value then waits for next start instruction
  //interrupts on completion of conversion
  ADC_init(__MSP430_BASEADDRESS_ADC__,ADC_SAMPLEHOLDSOURCE_SC,ADC_CLOCKSOURCE_ADCOSC,ADC_CLOCKDIVIDER_512);
  ADC_enable(__MSP430_BASEADDRESS_ADC__);
  ADC_setupSamplingTimer(__MSP430_BASEADDRESS_ADC__,ADC_CYCLEHOLD_16_CYCLES,ADC_MULTIPLESAMPLESDISABLE);
  ADC_configureMemory(__MSP430_BASEADDRESS_ADC__,ADC_INPUT_A5,ADC_VREFPOS_AVCC,ADC_VREFNEG_AVSS);
  ADC_enableInterrupt(__MSP430_BASEADDRESS_ADC__,ADC_COMPLETED_INTERRUPT);
}

bool isADCFinished()
{
  return adcFinished;
}

int16_t lastConversionValue()
{
  adcFinished = false;
  return adcValue;
}