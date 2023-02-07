/*
 * OccupancyDetector.c
 *
 *  Created on: Jan 30, 2023
 *      Author: Ayo Overton
 */
#include <msp430.h>

void gpioInit();

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    gpioInit();                 // Initialize all GPIO Pins for the project


    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode

    #define i()                 // Counter Variable



    while(1)
    {

        if (!(P4IN & BIT1))             // If Push Button Switch (P4.1) is pressed
        {
            int i = 0;                  // Initializes Counter Variable to 0

            do
            {                           // Warning Mode: Occurs until 10 seconds pass or the button is let go
                P6OUT &= ~BIT6;         // Turn off green LED
                P1OUT ^= BIT0;          // Toggle red LED on and off

                __delay_cycles(200000);             // Delay for 200000*(1/MCLK)=0.2s

                i = i + 1;              // Add 1 to the counter after every cycle

                if ((P4IN & BIT1))      // If the button is let go before 10 seconds, go to Armed state
                   {
                       i = 0;
                       break;
                   }

            }

            while (i < 20);

            do  // ALERT Mode: Occurs after the system has been in Warning mode for 10 seconds, or the 4.1 button has been released
            {
                P1OUT |= BIT0;          // Red LED is on and stays solid

                    if (!(P2IN & BIT3))  // If the button at P2.3 is pressed,
                    {
                        i = 0;                  // Set i equal to 0
                        P1OUT &= ~BIT0;         // Set P1.0 to off
                        P6OUT ^= BIT6;          // Toggle P6.6 on and off
                        __delay_cycles(3000000);             // Delay for 100000*(1/MCLK)=0.1s
                    }
            }

            while (i == 20);

        }


        else
        {
            P1OUT &= ~BIT0;         // Set P1.0 to off
            P6OUT ^= BIT6;          // Toggle P6.6 on and off
            __delay_cycles(3000000);             // Delay for 3000000*(1/MCLK)=3s
        }

    }
    return 0;
}


void gpioInit()
{
   // Setting Directions of Pins

       P1DIR |= BIT0;              // Configure P1.0 to an Output
       P6DIR |= BIT6;              // Configure P6.6 to an Output
       P2DIR &= ~BIT3;             // Configure P2.3 to an Input
       P4DIR &= ~BIT1;             // Configure P4.1 to an Input



   // Configuring Pullup Resistors per MSP430FR2355 Family User Guide
   /*
    *   PXDIR | PXREN | PXOUT | I/O Configuration
    *     0       0       X     Input
    *     0       1       0     Input with Pull Down Resistor
    *     0       1       1     Input With Pull Up Resistor
    *     1       X       X     Output
    */

       P2REN |= BIT3;               // Enable Resistor on P2.3
       P2OUT |= BIT3;               // Configures the Resistor on P2.3 to be Pullup

       P4REN |= BIT1;               // Enable Resistor on P4.1
       P4OUT |= BIT1;               // Configures the Resistor on P4.1 to be Pullup

}
