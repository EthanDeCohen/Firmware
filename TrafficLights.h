#include <msp430.h> 

#define RLED BIT0
#define YLED BIT1
#define GLED BIT2
#define PEDRED BIT5
#define PEDGREEN BIT4
#define BUTTON BIT3
int initialRun = 1;
int count=0;
int State=1;
int BUTTON1 = 0;
void main(void)
{

o    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    P1DIR = RLED + YLED + GLED  + PEDGREEN  +PEDRED; // Assign as output
   // P1REN |= BIT3;
    P1IE = BIT3;
    P1IES = BIT3;
    P1IFG = 0x00;
    __enable_interrupt();
    //_BIS_SR(LPM4_bits  + GIE);        // Enter LPM0 w/ interrupt

    while(1)
    {


    switch(State)
    {
        case 1:

        count=0;
       // P1IE = BIT3; // P1.3 interrupt enaGLED
       // P1IFG &= ~BIT3; // P1.3 IFG cleared
        P1OUT = GLED|PEDRED; // Turns on GLED
        __delay_cycles(60000000);        //Delays before turning on the GLED to prevent accidents
        while(count<30){

            if (BUTTON1=1){

            State = 2;

            break;}
        count++;

            __delay_cycles(1000000);
        }

        State =2 ;
        break;
        case 2:
        BUTTON1=0;
        P1OUT = YLED|PEDRED; // Turns on YLED
        __delay_cycles(5000000);

        State=3;
        break;

        case 3:
        P1OUT = RLED|PEDGREEN; //Turns on RLED;
        __delay_cycles(15000000);
         State=4;
        break;

        case 4:
        P1OUT = RLED + YLED + PEDRED;
        __delay_cycles(5000000);
        State = 1;
        break;
        default: State = 1;
        count = 0;
        break;
    }
    }
}

# pragma vector=PORT1_VECTOR
__interrupt void PORT_ISR(void)
       {BUTTON1=1 ;

         P1IFG = 0x00; }       // Enter LPM0 w/ interrupt

