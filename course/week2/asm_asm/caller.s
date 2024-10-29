	.text			# Define beginning of text section
	.global	_start		# Define entry _start

_start:
	li x6, 3		# x6 = 3
    li x7, 4		# x7 = 4
    mv a0, x6
    mv a1, x7

    jal callee

    mv x5, a0

stop:
	j stop			# Infinite loop to stop execution

	.end			# End of file
