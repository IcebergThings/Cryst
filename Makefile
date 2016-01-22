#/=============================================================================
#/ ■ Makefile
#/-----------------------------------------------------------------------------
#/   GENERAL 
#/=============================================================================

CC=clang++ -m32
CCLD=ld -m32
ARCH=i686

C_SOURCES = $(shell find . -name "*.cpp")
C_OBJECTS = $(patsubst %.cpp, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.asm")
S_OBJECTS = $(patsubst %.asm, %.o, $(S_SOURCES))

C_FLAGS = -c -Wall -m32 -ggdb -nostdinc -fno-builtin -fno-stack-protector -I. -O2
LD_FLAGS = -T scripts/kernel.ld -m elf_i386 -lgcc
ASM_FLAGS = -f elf32 -g -F stabs

all: mine.bin
run: all
	qemu-system-i386 -kernel mine.bin
debug: all
	qemu-system-i386 -kernel mine.bin -gdb tcp::1234 -S &
	sleep 1 # gdb要等qemu就绪
	cgdb -x gdbinit
clean:
	rm -rf isodir
	rm -f ${C_OBJECTS} ${S_OBJECTS} mine.bin
.PHONY: all run clean

.cpp.o: .c
	@echo 编译C++代码文件 $< ...
	$(CC) $(C_FLAGS) $< -o $@

boot.o: boot.asm
	@echo 编译multiboot文件 $< ...
	nasm $(ASM_FLAGS) $<

.asm.o: .c
	@echo 编译nasm汇编文件 $< ...
	nasm $(ASM_FLAGS) $<
	
mine.bin: ${C_OBJECTS} ${S_OBJECTS}
	${CCLD} -g -T linker.ld -o mine.bin -O2 -nostdlib $^

