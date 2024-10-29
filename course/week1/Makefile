gc:
	gcc -o 1 1.c

gc_clean:
	rm -f 1

riscv32:
	riscv32-unknown-elf-gcc -o 1_riscv32 1.c
	qemu-riscv32 1_riscv32

riscv32_clean:
	rm -f 1_riscv32

riscv64:
	riscv64-unknown-linux-gnu-gcc -o 1_riscv64.elf 1.c
	qemu-riscv64 -L /opt/vlab/riscv64/sysroot/ 1_riscv64.elf
	# qemu-system-riscv64 1_riscv64.elf                         *wrong*

riscv64_clean:
	rm -f 1_riscv64.elf