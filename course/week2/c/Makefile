EXEC = test

CROSS_COMPILE = riscv64-unknown-linux-gnu-
CC = ${CROSS_COMPILE}gcc

QEMU = qemu-riscv64
QFLAGS = -L /opt/vlab/riscv64/sysroot/

.DEFAULT_GOAL := all
all:
	@${CC} ${EXEC}.c -o ${EXEC}.elf

.PHONY : run
run: all
	@${QEMU} ${QFLAGS} ${EXEC}.elf

.PHONY : clean
clean:
	rm -rf *.elf