//MM Sorter
//main.c
//Last Modified: 16/03/2016
//Run ADC after enabling each LED
//Author: Ian Bowyer

#include "sensor.h"
#include "myAdc.h"

void sensorInit()
{
  GPIO_setAsOutputPin(RED_LED_PORT, RED_LED_PIN);
  GPIO_setAsOutputPin(GREEN_LED_PORT, GREEN_LED_PIN);
  GPIO_setAsOutputPin(BLUE_LED_PORT, BLUE_LED_PIN);
  
  adcInitForSensor();
}
struct colour runSensor()
{
  struct colour runResults;
  
  //enable lower bank LEDs
  GPIO_setOutputLowOnPin(RED_LED_PORT, RED_LED_PIN);
  GPIO_setOutputLowOnPin(GREEN_LED_PORT, GREEN_LED_PIN);
  GPIO_setOutputLowOnPin(BLUE_LED_PORT, BLUE_LED_PIN);
  
  /*RED LED***********************************************************/
  runResults.red_value = getLDRVoltageForLED(RED_LED_PORT, RED_LED_PIN);
  
  /*GREEN LED********************************************************/
  runResults.green_value = getLDRVoltageForLED(GREEN_LED_PORT, GREEN_LED_PIN);
  
  /*BLUE LED*********************************************************/
  runResults.blue_value = getLDRVoltageForLED(BLUE_LED_PORT,BLUE_LED_PIN);
  
  return runResults;
  
}

int16_t getLDRVoltageForLED(uint8_t selectedPort, uint16_t selectedPins)
{
  //enable desired pins to turn on LED
  
  GPIO_setOutputHighOnPin(selectedPort, selectedPins);
  
  
  //delay so LDR can settle
  __delay_cycles(LED_DELAY);
  
  //read from LDR
  ADC_startConversion(__MSP430_BASEADDRESS_ADC__,ADC_SINGLECHANNEL);
  
  //wait for completion interrupt from ADC
  while(!isADCFinished()) 
  {
    __delay_cycles(1000);
  }
 
  int16_t temp = lastConversionValue();
  
   //disable LED
  GPIO_setOutputLowOnPin(selectedPort, selectedPins);
   
  return temp;
}