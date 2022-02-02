/************************************************************************************************************
 * Date of creation:10/3/2021
 * Authors: Hetisha Patel 
 * Implementation of basic stopwatch which counts upto 9 seconds and increments in steps of .1 sec
 * First switch press start the stopwatch, second switch press stops it and third resets it
 * Program uses interrupt for timer and switch press
 * The count is displayed on 2 seven segment leds
*************************************************************************************************************/

#include <msp430.h>
#define milisec 100                   // 100ms
char switchPress=0;                   // switchPress counter
unsigned int count=0;
void initTimer_A(void);
void delay_ms(unsigned int ms);
void setup(void);
void display(char cnt, char x);



int main(void)
{
     setup();                          // initial setup for pins
	 initTimer_A();                    // initialize timer
	 __enable_interrupt();             // enable timer
	 char counti=0,countf=0;           // counter for countfger and float led

	 while(1){
	     if (switchPress==0){          // if switch is not pressed
	         display(countf,1);        // initial set both led display 0
	         display(counti,2);
	     }
	     else if(switchPress==1){      // switch is press one time

	         if(count >= milisec){    // milisec is defined with value 100 for 0.1 sec

             countf++;                // increment float counter
             display(countf,1);       // display the countf
             if(counti==9 && countf==9){   // if both count goes to 9 reset it to 0 and display
               counti=0;
               countf=0;
               display(countf,1);
               display(counti,2);
                  }
             if(countf>9){           // if float count> 9 reset float count and increment int count and display
              countf=0;
              counti++;
              display(counti,2);

             }

             count=0;                // set count for timer to 0
	         }

	     }
	     else if(switchPress==2){   // if switchPress =2
	         // stay at that state
	         P1OUT &= P1OUT;
	         P2OUT &= P2OUT;
	     }

	     // if switchPress==3 -> reset both led
	     else if(switchPress==3){
	         switchPress=0;        // reset switch count to 0 and counter to 0
	         counti=0;
	         countf=0;
	     }
	 }
 }
//-----------------------------------------------------------------------------------------------------

void setup(void){
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR &= ~BIT7;             // input
    P1DIR = 0x7F;               // Set P1.0 to P1.6 to output direction
    P1IE |=  BIT7;              // P1.7 countfrrupt enabled
    P1IES |= BIT7;              // P1.7 Hi/lo edge
    P1IFG &= ~BIT7;             // P1.7 IFG cleared
    P2SEL &= 0x3F;              // clear P2.6 & P2.7  in P2SEL to use as gpio
    P2DIR |= 0xFF;              // set port P2 as output
}
//-------------------------------------------------------------------------------------------------------

void initTimer_A(void) {        // initialize timer and configuration
    TACCR0 = 0;                 // Initially, Stop the Timer
    TACCTL0 |= CCIE;            // Enable countfrrupt for CCR0.
    TACTL = TASSEL_2 + ID_0 + MC_1; //Select SMCLK, SMCLK/1 , Up Mode
}
//--------------------------------------------------------------------------------------------------------

//Timer ISR
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A_CCR0_ISR(void) {
     count++;                  // update gobal variable count
   }
//--------------------------------------------------------------------------------------------------------

// switch ISR
#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void) {
   delay_ms(200);             // delay to account for debouncing
   switchPress++;             // update switchPress
   if (switchPress==1){  TACCR0 = 1000-1; }  //  start timer if switchPress is 1
   P1IFG &= ~BIT7;            // P1.7 IFG cleared
}
//--------------------------------------------------------------------------------------------------------

void delay_ms(unsigned int ms)   // custom fuction for 1ms delay
{
    while (ms)
    {
        __delay_cycles(1000); //1000 for 1MHz and 16000 for 16MHz
        ms--;
    }
}
//--------------------------------------------------------------------------------------------------------

void display(char cnt,char x){    // to display count which takes port number as argument
    switch(cnt)
    {
    case 0:
        if (x==1){
    P1OUT=0x40;}
        else if(x==2){P2OUT=0x40;}
    break;
    case 1:
        if(x==1){
    P1OUT=0x79;}
        else if(x==2){ P2OUT=0x79;}
    break;
    case 2:
        if(x==1){
    P1OUT=0x24;}
        else if(x==2){P2OUT=0x24;}
    break;
    case 3:
        if(x==1){
    P1OUT=0x30;}
        else if(x==2){P2OUT=0x30;}
    break;
    case 4:
        if(x==1){
    P1OUT=0x19;}
        else if(x==2){P2OUT=0x19;}
    break;
    case 5:
        if(x==1){
    P1OUT=0x12;}
        else if(x==2){P2OUT=0x12;}
    break;
    case 6:
        if(x==1){
    P1OUT=0x02;}
        else if(x==2){P2OUT=0x02;}
    break;
    case 7:
        if(x==1){
    P1OUT=0x78;}
        else if(x==2){P2OUT=0x78;}
    break;
    case 8:
        if(x==1){
    P1OUT=0x00;}
        else if(x==2){P2OUT=0x00;}
    break;
    case 9:
        if(x==1){
    P1OUT=0x10;}
        else if(x==2){P2OUT=0x10;}
    break;
    }
}
//--------------------------------------------------------------------------------------------------------
