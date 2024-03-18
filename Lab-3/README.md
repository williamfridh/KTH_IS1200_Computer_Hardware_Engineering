# Lab-3

**This document contains answers we as students had to answer while presenting lab 3.**

# Questions for Assignment 1

## Test pressing BTN3 and BTN2 at the same time. What happens? Why?

### Answer: 
When you press the buttons both numbers get the input given by the switches.

## Three device-registers for input/output control are TRISE, TRISESET, and TRISECLR. Their functions are related. How? What are the differences?

### Answer: 
Their function is to set what is to be an input/output. Using TRISE you set the value of a specific bit to either 1 or 0. 
And with TRISESET you set the bit to be only 1, and TRISECLR you set a bit to 0.  

## In the generated assembly code, in which MIPS register will the return values from functions getbtns and getsw be placed in. You should be able to answer this question without debugging the generated assembly code.

### Answer:
A function return value in assembly is either stored in $v0 or $v1, there are only those two registers for return values.


## In this exercise, we explained which bits that should be used in Port D and Port E. How can you find this information in the PIC32 and ChipKIT manuals? Be prepared to demonstrate how to find this information in the manuals. 

### Answer:
http://ww1.microchip.com/downloads/en/DeviceDoc/61143H.pdf

Go in to the manual and search for the relevenat registers map.


# Questions for Assignment 2

## When the time-out event-flag is a "1", how does your code reset it to "0"?

### Answer: 
In line 77 we use IFS(0) = 0, and we clear the flag. 


## What would happen if the time-out event-flag was not reset to "0" by your code? Why?

### Answer:
The if statement in line 78 will only depend on the timeoutcount variable, meaning that the program will run at "normal speed" i.e not slowed down by interrupts.

## Which device-register (or registers) must be written to define the time between time-out events? Describe the function of that register (or of those registers).

### Answer: 
PR2, TMR2 and T2CON. PR2 (period register) is the period which the timer will count up towards. TMR2 (timer register) is the starting/default value that the timer will start on after a reset. T2CON (control register) is what stops the timer and sets the prescale value. It sets all the bits to the given value.     

## If you press BTN3 quickly, does the time update reliably? Why, or why not? If not, would that be easy to change? If so, how?

### Answer:
The time only updates on each tick. This can be fixed by putting the button update in an infinity loop.

# Questions for Assignment 3

## When the time-out event-flag is a "1", how does your code reset it to "0"?

### Answer: 
In line 77 we use IFS(0) = 0, and we clear the flag. 

## What would happen if the time-out event-flag was not reset to "0" by your code? Why?

### Answer: 
If the flag isn't cleard atleast once then the prime counting function doesn't initiate, and the timer count is only dependent in the variable timeoutcount. //CONTINUE ON THIS look at vectors.S

## From which part of the code is the function user_isr called? Why is it called from there?

### Answer: 
user.isr is called via the interrupt handler from vectors.S. Because we look for the interrupts, and vectors.S handles interrupts. 

## Why are registers saved before the call to user_isr? Why are only some registers saved?

### Answer:
We push the registers because the program will modify the values, and we want them not to be modified. 

## Which device-register (or registers), and which processor-register (or registers) must be written to enable interrupts from the timer? Describe the functions of the relevant registers.

### Answer:
IECSET(0) and enable_interrupt are used to enable interrupts. IECSET targets the interrupt registers which enables interrupts for the device register. And enable_interrupts() targets the processor register that enables interrupts in the proccesor.