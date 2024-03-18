/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   //Pontus Åhlin 
   //William Fridh
   //2023-02-10 

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x0000;
int prime = 1234567;                  //Initilise global prime number
int timeoutcount = 0;                 //A global counter used in labwork
volatile int * porte = (volatile int *) 0xbf886110;                   // Supposed to be inside labwork(), but unnecesarry
int ledTime = 0;                                                      //Int time counter 


char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{                                         //Detect and interrupt flag

  if(IFS(0) & 0x80){
    ledTime++;
    *porte = ledTime;
    IFS(0) = IFS(0) & 0xffffff7f;         //reset specific flag 
  }



  if(IFS(0) & 0x100){
    timeoutcount++;
    IFS(0) = IFS(0) & 0xfffffeff;                                                   //Clear flags
    if(timeoutcount == 10){
      time2string(textstring, mytime);
      display_string(3, textstring);
      display_update();
      tick(&mytime);
      timeoutcount = 0;
    }
  }
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int * trise = (volatile int *) 0xbf886100;                 // Defined pointer to TRISE
  *trise = *trise & 0xffffff00;                                       // Set ports 0-7 as outputs
  *porte = 0;

  TRISDSET = 0xfe0;                   //Set switches 1,2,3,4 and buttons 2,3,4 as inputs 
  T2CON = 0x70;                       //Stopping timer and setting the prescaler to 1/256
  PR2 = ((80000000 / 256)/ 10);       //Setting the period for the timer
  TMR2 = 0;                           //Ticks to PR2
  IECSET(0) = 0x100;                  //Enable interrupts
  IPC(2) = 0xC;                       //Enable a interrupt priority
  enable_interrupt();
  T2CONSET = 0x8000;                  //Starting timer


  IECSET(0) = 0x80;                   //Enable interrupts for External interrupt 1
  IPC(1) = 0xC;                       //Set priority for timer 1 




  return;
}



/* This function is called repetitively from the main program */

void labwork( void )
{
    prime = nextprime(prime);
    display_string(0, itoaconv(prime));
    display_update();
}
