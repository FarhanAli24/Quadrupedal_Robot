/*
 * SERVO.C
 *
 *  Created on: Apr 7, 2023
 *      Author: farha
 */
#include "msp.h"
#include "msp432.h"
#include <stdint.h>
#include <stdbool.h>
#include "Clock.h"
#include "Clock.h"
#include "CortexM.h"


void sholder(int degrees)
{
    P2DIR |= BIT4;
    P2SEL1 &=  ~BIT4;
    P2SEL0 |=  BIT4;

    uint16_t Pulse = (degrees * 6000 / 270) + 1500; // Converting to degrees of rotation

    TA0CTL &= ~0x0030;
    TA0CTL |= 0x0200; TA0CTL &= ~0x0100;  // choose SMCLK for the clock source
    TA0CTL |= 0x0080; TA0CTL &= ~0x0040; //SM CLK Divider

    TA0CCTL1 |= 0x00E0;
    TA0CCR0 = 59999; // clocks for 20ms period
    TA0CCR1 = Pulse; // clocks for 10% duty cycle

    TA0CTL |= 0x0010; // UPMODE
}

 void thigh (int degrees)
 {
     P6DIR |= BIT6;
     P6SEL1 &=  ~BIT6;
     P6SEL0 |=  BIT6;

     uint16_t Pulse = (degrees * 6000 / 270) + 1500;//converting to degrees of rotation

     TA2CTL |= 0x0200; TA2CTL &= ~0x0100;  // choose SMCLK for the clock source
     TA2CTL |= 0x0080; TA2CTL &= ~0x0040; //SM CLK Divider

     TA2CCTL3 |= 0x00E0;
     TA2CCR0 = 59999; // clocks for 20ms period
     TA2CCR3 = Pulse; // clocks for 10% duty cycle

     TA2CTL |= 0x0010; // UPMODE

 }

void body (int degrees)
{
  P8DIR |= BIT2;
  P2SEL1 &=  ~BIT2;
  P2SEL0 |=  BIT2;

  uint16_t Pulse = (degrees * 6000 / 270) + 1500;//converting to degrees of rotation

  TA3CTL |= 0x0200; TA3CTL &= ~0x0100;  // choose SMCLK for the clock source
  TA3CTL |= 0x0080; TA3CTL &= ~0x0040; //SM CLK Divider

  TA3CCTL2 |= 0x00E0;
  TA3CCR0 = 59999; // clocks for 20ms period
  TA3CCR2 = Pulse; // clocks for 10% duty cycle

  TA3CTL |= 0x0010; // UPMODE

}

 void InterruptInit(void) {
     TA1CTL     = 0x0252;      //enable timer SMCLK/2 and UP mode
                               //timerA2 interrupt enabled
     TA1EX0     = 0x0002;      //divide by 3 (total of /6)
     TA1CCR0    = 62499;       //configured for 125ms

     NVIC -> ISER[1] = 0x00000008;
     TA1CTL  &= ~ BIT0;        //clear any pending flag (TAIFG)
     TA1R = 0;                 //reset timer to zero
     EnableInterrupts();       //global interrupt enable
     return;
 }




