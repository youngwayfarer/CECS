    .text			# Define beginning of text section
	.global	_start		# Define entry _start
    .extern multiply

_start:
    la sp, stack_top

	li x6, 3		# x6 = 3
    li x7, 4		# x7 = 4
    mv a0, x6
    mv a1, x7

    call multiply

    mv x5, a0

stop:
	j stop			# Infinite loop to stop execution


# 定义栈空间
.section .bss
.align 12
stack:
    .space 4096       # 分配4KB的栈空间
stack_top:

    .end			# End of file