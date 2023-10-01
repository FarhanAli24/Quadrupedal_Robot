#include "msp.h"
#include "msp432.h"
#include <stdint.h>
#include <stdbool.h>
#include "Clock.h"
#include "Clock.h"
#include "CortexM.h"
#include "SERVO.h"
#include "Timer.h"
#include "Init_Ports.h"

//sholder 60 degree max
/**
 * main.c
 */

volatile bool wasInterrupt = false;
void PORT5_IRQHandler(void)
{
    /*
    wasInterrupt = 1;//tell main about interrupt
    P5IFG &= 0x00; // clear interrupt flags
    */

    uint16_t status = TA2IV;
    //set flag only if correct interrupt
    if (status == 0x000E) wasInterrupt = true;
}


void main(void)
{
    bool reverse = false;

    PORT5_IRQHandler();
    Port5_Init();
    Port1_Init();
    P5OUT &= 0b00000000;


	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
    Clock_Init48MHz();
    EnableInterrupts();
    InterruptInit();

    int direction = 1; // will be used to sweep from -90 to +90 degrees

    uint16_t stepSize = 0;

    //thigh(120);
    //sholder(50);

/*
     thigh(140);
    Clock_Delay1ms(20);
    sholder(90);
    Clock_Delay1ms(20);
    body(90);
    Clock_Delay1ms(500);
*/
    enum motor_states { position1, position2, position3, position4} state, prevState;

    state = position1;                     //start state
    prevState = !position1;               //used to know when the state has changed
    uint16_t stateTimer;               //used to stay in a state
    bool isNewState;

    body(270);

    while(1)
    {
        if ((P1IN & BIT1) == 0)
       { //determine if S1 is pushed - remember it is active low

            wasInterrupt = true;
           while((P1IN & BIT1) == 0); //wait here for pin to be released.

       }

        if(((P1IN & BIT4) == 0) && reverse == false)
        {
            reverse = true;
            while((P1IN & BIT4) == 0);
        }

        if(((P1IN & BIT4) == 0) && reverse == true)
        {
            reverse = false;
            while((P1IN & BIT4) == 0);
        }


        if(reverse == true)
        {
            sholder(90);
            Clock_Delay1ms(200);
            thigh(140);
            Clock_Delay1ms(200);
            sholder(160);
            Clock_Delay1ms(200);
            thigh(80);
            Clock_Delay1ms(200);



        }


        isNewState = (state != prevState);
         prevState = state;  //save state for next time

        switch(state) {

        case position1:

            if((wasInterrupt != true) || reverse  == false)
            {
            thigh(80);

            Clock_Delay1ms(500);
            state = position2;
            }
            break;

        case position2:
            if((wasInterrupt != true) || reverse  == false)
            {
            sholder(160);
            Clock_Delay1ms(500);
            state = position3;
            }
            break;
        case position3:
            if((wasInterrupt != true) || reverse  == false)
            {
            thigh(140);
            Clock_Delay1ms(500);
            state = position4;
            }
            break;

        case position4:
            if((wasInterrupt != true) || reverse  == false)
            {
               sholder(90);
               Clock_Delay1ms(500);
               state = position1;
            }
           break;

        }
    }
}
