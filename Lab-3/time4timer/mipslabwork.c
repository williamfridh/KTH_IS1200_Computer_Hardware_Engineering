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

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int * trise = (volatile int *) 0xbf886100;                 // Defined pointer to TRISE
  *trise = *trise & 0xffffff00;                                       // Set ports 0-7 as outputs

  TRISDSET = 0xfe0;                   //Set switches 1,2,3,4 and buttons 2,3,4 as inputs 
  T2CON = 0x70;                       //Stopping timer and setting the prescaler to 1/256
  PR2 = ((80000000 / 256)/ 10);       //Setting the period for the timer
  TMR2 = 0;                           //Ticks to PR2
  T2CONSET = 0x8000;                  //Starting timer



  return;
}



/* This function is called repetitively from the main program */
volatile int * porte = (volatile int *) 0xbf886110;                   // Supposed to be inside labwork(), but unnecesarry
int timeoutcount = 0;                                                 //A global counter used in labwork
int ledTime = 0;                                                      //Int time counter 
void labwork( void )
{
  int btn = getbtns();
  //mytime = getsw();

  if(btn & 0x8){                                                      //Check if button 4 is pressed, if yes get switch
      mytime = (mytime & 0x0fff) | (getsw() << 12);                                   
  }
 
 if(btn & 0x4){                                                      //Check if button 3 is pressed, if yes get switch
      mytime = (mytime & 0xf0ff) | (getsw() << 8);                                   
  }

 if(btn & 0x2){                                                      //Check if button 2 is pressed, if yes get switch
      mytime = (mytime & 0xff0f) | (getsw() << 4);                                   
  }



  //delay( 1000 );

  if(IFS(0) & 0x100){                                             //Detect and interrupt flag
    timeoutcount++;                                               //Increment global counter 
    IFS(0) = 0;                                                   //Clear flags
    if(timeoutcount == 10){                                       //If there as been 10 timeout event flags then the timer value and LEDs will update
      time2string( textstring, mytime );
      display_string( 3, textstring );
      display_update(); 
      tick( &mytime );
      timeoutcount = 0;
      *porte = ledTime;                                           //Set let value to mytime.
      ledTime++;
    }
  }
  display_image(96, icon);

}
