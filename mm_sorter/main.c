#include <msp430.h>
#include <driverlib.h>

#include "sensor.h"
#include "servoController.h"
#include "sorter.h"
#include "interface.h"

void init();
bool isFinished();

bool SW1_interruptFlag_ = false;
bool SW2_interruptFlag_ = false;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PMM_unlockLPM5();
    
    bool running = false;
    init();
    
    __enable_interrupt();
    
    struct colour detectedColour;
    
    while(1)
    {
          if (SW2_interruptFlag_)
          {
            SW2_interruptFlag_ = false;
            running = true;
            
          }
          else if (SW1_interruptFlag_)
          {
            SW1_interruptFlag_ = false;
            showNextRGBValue_Debug();
            updateRGBValues_Debug(detectedColour);            
          }
          
          if (running)
          {
            //wait for mm to drop
            __delay_cycles(2000000);
            
            //move seperator to colour sensor
            changeDutyCycle(0x39);
            
            //run sensor
            detectedColour = runSensor();
            
            //run sorter
            
            //move seperator to exit
            changeDutyCycle(0x60);
            
            //wzit for mm to drop
            __delay_cycles(1000000);
            
            //move seperator to entrance
            changeDutyCycle(0x20);
            
            //update ui values
            updateRGBValues_Debug(detectedColour);
            
            running = !isFinished();
          }
          
          __delay_cycles(10000);
    }
}

void init()
{
  sensorInit();
  InterfaceInit();
  seperatorInit();
  
  // Configure button S1 interrupt
  GPIO_selectInterruptEdge(GPIO_PORT_P1, GPIO_PIN3, GPIO_LOW_TO_HIGH_TRANSITION);
  GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN3);  

  GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN3);

  GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN3);
  
  // Configure button S2 interrupt
  GPIO_selectInterruptEdge(GPIO_PORT_P1, GPIO_PIN4, GPIO_LOW_TO_HIGH_TRANSITION);
  GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);  

  GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN4);

  GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);
}

//returns true if finsihed and false if not
bool isFinished()
{
  return true;
  //todo detect if finished automatically
}

#pragma vector = PORT1_VECTOR
__interrupt void P1_ISR(void)
{
  switch(__even_in_range(P1IV,P1IV_P1IFG7)) 
  {
     case P1IV_P1IFG3: //It is SW1
      	SW1_interruptFlag_ = 1;
    	GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN3);
      break;
      
      case P1IV_P1IFG4:  //It is SW2
    	SW2_interruptFlag_ = 1;
    	GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN4);
      break;
  } 

}

