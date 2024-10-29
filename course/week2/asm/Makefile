EXEC = test

SRC = ${EXEC}.s

GDBINIT = ./gdbinit

CROSS_COMPILE = riscv64-unknown-linux-gnu-
CFLAGS = -nostdlib -fno-builtin -march=rv64g -mabi=lp64 -g -Wall

QEMU = qemu-system-riscv64
QFLAGS = -nographic -smp 1 -machine virt -bios none

GDB = gdb-multiarch
CC = ${CROSS_COMPILE}gcc

.DEFAULT_GOAL := all
all:
	@${CC} ${CFLAGS} ${SRC} -Ttext=0x80000000 -o ${EXEC}.elf

.PHONY : debug
debug: all
	@echo "Press Ctrl-C and then input 'quit' to exit GDB and QEMU"
	@echo "-------------------------------------------------------"
	@${QEMU} ${QFLAGS} -kernel ${EXEC}.elf -s -S &
	@${GDB} ${EXEC}.elf -q -x ${GDBINIT}

.PHONY : clean
clean:
	rm -rf *.o *.elf