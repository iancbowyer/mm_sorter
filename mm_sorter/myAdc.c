#include "myAdc.h"
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
    break;
  }
}

void adcInitForSensor()
{
  //configure pin 8.1
  GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P8, GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION);
  
  //setup ADC to take value from 8.1 and convert to binary
  //converts one value then waits for next start instruction
  //interrupts on completion of conversion
  ADC_init(__MSP430_BASEADDRESS_ADC__,ADC_SAMPLEHOLDSOURCE_SC,ADC_CLOCKSOURCE_ADCOSC,ADC_CLOCKDIVIDER_16);
  ADC_enable(__MSP430_BASEADDRESS_ADC__);
  ADC_setupSamplingTimer(__MSP430_BASEADDRESS_ADC__,ADC_CYCLEHOLD_16_CYCLES,ADC_MULTIPLESAMPLESDISABLE);
  ADC_configureMemory(__MSP430_BASEADDRESS_ADC__,ADC_INPUT_A9,ADC_VREFPOS_AVCC,ADC_VREFNEG_AVSS);
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