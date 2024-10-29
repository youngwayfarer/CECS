	.text			# Define beginning of text section
	.global	callee		# Define entry _start

callee:
	mul a0, a0, a1
    ret

	.end			# End of file
