  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,10		# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
  # ADD 
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
	
	
