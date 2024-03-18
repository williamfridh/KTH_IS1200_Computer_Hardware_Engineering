  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,1
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
hexasc:
	andi	$v0, $a0, 0xf		# Bitwise AND to target first 4 bits
	ble	$v0, 0x9, is_number	# Jump function if it's a number
	nop				# delay slot filler (just in case)
	addi 	$v0, $v0, 0x37		# Modify for letter
	jr	$ra			# Return
	nop				# delay slot filler (just in case)
is_number:
	addi 	$v0, $v0, 0x30		# Modify for number
	jr	$ra			# Return
	nop				# delay slot filler (just in case)
	
delay:
	li	$t2, 0
	li	$t3, 4711
delay_while:
	li	$t0, 0
	ble	$a0, $t2, delay_end
	nop
	addi	$a0, $a0, -1
delay_for:
	ble	$t3, $t0, delay_while
	nop
	addi	$t0, $t0, 1
	j	delay_for
	nop
delay_end:
	jr	$ra
	nop
	
time2string:

	PUSH	($s0)			# Push data
	PUSH	($s1)			# Push data
	PUSH	($s2)			# Push data
	PUSH	($s3)			# Push data
	PUSH	($s4)			# Push data
	PUSH	($s5)			# Push data
	PUSH	($ra)			# Push data
	PUSH	($a0)			# Push data
	
	li	$s0 0x00		# Prepare null bytes
	
	andi 	$s1, $a1, 0xf		# Save lower sec
	move	$a0, $s1		# Move data from t1 to a0
	jal	hexasc			# Call hex asc convertion
	nop				# delay slot filler (just in case)
	move	$s1, $v0		# Move res to $t1
	
	andi 	$s2, $a1, 0xf0		# Save heighet sec
	srl	$s2, $s2, 4		# Shift minuts to lsb
	move	$a0, $s2		# Move from $t2 to $ao
	jal	hexasc			# Call hex asc convertion
	nop				# delay slot filler (just in case)
	move	$s2, $v0		# Move res to $t2
	
	li	$s3 0x3A		# Prepare semicolon code
	
	andi 	$s4, $a1, 0xf00		# Save lower min
	srl	$s4, $s4, 8		# Shift minuts to lsb
	move	$a0, $s4		# Move from $t4 to $ao
	jal	hexasc			# Call hex asc convertion
	nop				# delay slot filler (just in case)
	move	$s4, $v0		# Move res to $t4
	
	andi 	$s5, $a1, 0xf000	# Save higher min
	srl	$s5, $s5, 12		# Shift minuts to lsb
	move	$a0, $s5		# Move from $t5 to $ao
	jal	hexasc			# Call hex asc convertion
	nop				# delay slot filler (just in case)
	move	$s5, $v0		# Move res to $t5
	
	POP	($a0)			# Pop pushed data
	
	# Last second isn't 9
	sb	$s0, 5($a0)		# Store empty bytes
	sb	$s1, 4($a0)		# Store lower sec
	sb	$s2, 3($a0)		# Store higher sec
	sb	$s3, 2($a0)		# Store semicolon code
	sb	$s4, 1($a0)		# Store lower min
	sb	$s5, 0($a0)		# Store higher min
	
	POP	($ra)			# Pop pushed data
	POP	($s5)			# Pop pushed data
	POP	($s4)			# Pop pushed data
	POP	($s3)			# Pop pushed data
	POP	($s2)			# Pop pushed data
	POP	($s1)			# Pop pushed data
	POP	($s0)			# Pop pushed data
	
	jr $ra
	nop
	
