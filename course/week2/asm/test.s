# Add
# Format:
#	ADD RD, RS1, RS2
# Description:
#	The contents of RS1 is added to the contents of RS2 and the result is 
#	placed in RD.

	.text			# Define beginning of text section
	.global	_start		# Define entry _start

_start:
	li x6, 3		# x6 = 3
	li x7, 2		# x7 = 2
	mul x5, x6, x7		# x5 = x6 * x7

stop:
	j stop			# Infinite loop to stop execution

	.end			# End of file
