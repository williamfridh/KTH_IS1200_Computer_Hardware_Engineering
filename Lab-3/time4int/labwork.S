  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
  
 .data
 .text
 .global delay, time2string, enable_interrupt

 # hexmain.asm
 # Written 2015-09-04 by F Lundevall
 # Copyright abandonded - this file is in the public domain.

enable_interrupt:
	ei
	jr 	$ra
	nop

	
hexasc:
	andi	$v0, $a0, 0xf		#COPY LAST 4 LSB 
	ble	$v0, 0x9, smallerNum	#If the value of $v0 is smaller than 9 we go to smallNum 
	nop
	addi 	$v0, $v0, 0x37
	jr	$ra
	nop
	
smallerNum:	
	addi 	$v0, $v0, 0x30
	jr	$ra
	nop
 	 
delay:

    addi    $sp,$sp,-4        #PUSH
    sw    $a0,0($sp)

                    #$a0 is the parameter of ms 
    li    $t2, 0            #Value zero used for "while loop"
    li    $t3,3700         #The "GREATER THAN i" value in for loop


WhileLoop:
    li    $t0, 1            #Equivalent of i used in "for loop"
    ble     $a0, $t2, JumpBackToMain
    nop
    addi    $a0, $a0, -1        #Decrement for ms 

ForLoop:

    ble    $t3, $t0, WhileLoop
    nop
    addi    $t0, $t0, 1        #Increment for "for loop"
    j    ForLoop
    nop

JumpBackToMain:

    lw    $a0,0($sp)            #POP
    addi    $sp,$sp,4

    jr    $ra
    nop
	
time2string:

	#COPY VALUES FROM THE $A1 TO A NEW REGISTERS (T0-T3)	WHILE T4 IS THE "FINAL" REGISTER THAT WE ADD EVERYTHING TO 

	addi	$sp,$sp,-4
	sw	$ra,0($sp)
	
	addi	$sp,$sp,-4
	sw	$a0,0($sp)
	
	andi	$t0, $a1, 0xf000		#SHIFT 12 STEPS TO RIGHT 
	srl	$t0, $t0, 12
	
	andi	$t1, $a1, 0x0f00		#SHIFT 8 STEPS TO RIGHT 
	srl	$t1, $t1, 8
	
	andi	$t2, $a1, 0x00f0		#SHIFT 4 STEPS TO THE RIGHT  
	srl	$t2, $t2, 4
	
	andi	$t3, $a1, 0x000f		#SHIFT NOT NEEDED hexasc uses the values from the 4-LSB / LS-BYTE.

	li 	$t4, 0x00			#THE NULL BYTES
	li 	$t5, 0x3A			#THE SEMICOLON 


	move	$a0, $t0
	jal	hexasc 
	nop
	addi	$t0, $v0, 0
	
		
	move	$a0,$t1
	jal 	hexasc
	nop
	addi	$t1, $v0, 0

	
	move	$a0,$t2
	jal 	hexasc
	nop
	addi	$t2, $v0, 0
	
		
	move	$a0,$t3
	jal 	hexasc
	nop
	addi	$t3, $v0, 0			#PROCESS HERE IS SO T0-T3 GET THE HEXADECIMAL VALUES.
	
	
	lw	$a0,0($sp)
	addi	$sp,$sp,4
	
	lw	$ra,0($sp)
	addi	$sp,$sp,4
	
	sb 	$t4,5($a0)			#NULL BYTES
			
	sb 	$t3,4($a0)			#FIRST SECOND	
	
	sb	$t2,3($a0)			#SECOND SECOND 
	
	sb 	$t5,2($a0)			#THE SEMICOLON
	
	sb 	$t1,1($a0)			#FIRST HOUR 
	
	sb	$t0,0($a0)			#SECOND HOUR 
	

	jr	$ra
	nop
	
	
	








  #
  # Please add your own code below this line
  #

