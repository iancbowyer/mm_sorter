//MM Sorter
//main.c
//Last Modified: 18/04/2016
//Added support for viewing mm counts
//Author: Ian Bowyer

#include <msp430.h>
#include <driverlib.h>

//include header files for sub-systems
#include "sensor.h"
#include "servoController.h"
#include "sorter.h"
#include "interface.h"
#include "comparator.h"
#include "mm_colour_enum.h"
#include "rgb_enum.h"
#include "myAdc.h"
#include "mmCounts.h"

//prototype functions
void init();
bool isFinished();
void incrementCount(enum mmColours detectedMM);

//flag for sw1 and sw2 interrupts
bool SW1_interruptFlag_ = false;
bool SW2_interruptFlag_ = false;

struct mmCount numOfMMs;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PMM_unlockLPM5();
    
    //bools for running control logic for each switch
    bool running = false;
    bool running2 = false;
    
    //initialise systems
    init();
    
                                
    __enable_interrupt();
    
    //stores data returned from colour sensor
    struct colour detectedColour;
    //stores MM decision from comparator
    enum mmColours detectedMM;
    
    //initialise counts to 0
    numOfMMs.red = 0;
    numOfMMs.orange = 0;
    numOfMMs.yellow = 0;
    numOfMMs.brown = 0;
    numOfMMs.green = 0;
    numOfMMs.blue = 0;
    
    //number of mms sorted in current batch
    int mmSorted = 0;
        
    //main loop
    while(1)
    {     
          //switch 2 has interrupted
          if (SW2_interruptFlag_)
          {
            //ignore input from button for 0.1s
            __delay_cycles(100000);
            SW2_interruptFlag_ = false;
            
            //start sorting
            running = true; 
          }
          //switch 1 has interrupted
          else if (SW1_interruptFlag_)
          {
            SW1_interruptFlag_ = false;
            
            //update LCD with next value
            running2 = true;
          }
          if (running2)
          {
            //display next mm count on the LCD
            showNextCount();
            updateLCDWithCount(numOfMMs);
            
            running2 = false;
          }
          
          while (running)
          {
            //wait for an mm to enter seperator
            __delay_cycles(500000);
            
            //move seperator to colour sensor
            changeServoADutyCycle(0x32);
              
            //wait for mm to enter detection chamber
            __delay_cycles(300000);
              
            //run sensor
            detectedColour = runSensor();
             
            //compare sensor reading to calibration data
            detectedMM = decideColour(detectedColour);
            
            //increse count for detected MM by 1
            incrementCount(detectedMM);
               
            //run sorter
            moveSorter(detectedMM);
            __delay_cycles(1000000);
              
            //move seperator to exit
            changeServoADutyCycle(0x50);
              
            //wait for mm to drop
            __delay_cycles(700000);
             
            //move seperator to entrance
            changeServoADutyCycle(0x20);
                         
            //reset servo b
            changeServoBDutyCycle(0x20);
             
            __delay_cycles(1000000);
            
            //sorted one more from current batch
            mmSorted++;
            
            if (mmSorted == 1)
            {
              running = false;
              mmSorted = 0;
              updateLCDWithCount(numOfMMs);
            }
            
            //stop if the button is pressed
            if (SW2_interruptFlag_)
            {
              __delay_cycles(100000);
              SW2_interruptFlag_ = false;
              running = false;
              mmSorted = 0;
              updateLCDWithCount(numOfMMs);
            }
          
          }
    }
}

void incrementCount(enum mmColours detectedMM)
{
  //increment count for detected mm
  switch (detectedMM)
  {
  case red:
    numOfMMs.red++;
    break;
  case orange:
    numOfMMs.orange++;
    break;
  case brown:
    numOfMMs.brown++;
    break;
  case green:
    numOfMMs.green++;
    break;
  case yellow:
    numOfMMs.yellow++;
    break;
  case blue: 
    numOfMMs.blue++;
    break;
  }  
  
}

void init()
{
  //initialise colour sensor
  sensorInit();
  //iniitalise interface
  InterfaceInit();
  //initialise servos for seperator and sorter
  servoInit();
  
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

