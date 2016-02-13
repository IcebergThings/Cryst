#  Copyright 2016 Iceberg OS
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#==============================================================================
# ■ Makefile
#==============================================================================

#----------------------------------------------------------------------------
# ● 定义变量
#----------------------------------------------------------------------------
CC=clang++ -m32
CCLD=ld -melf_i386
ARCH=i686

C_SOURCES = $(shell find . -name "*.cpp")
C_OBJECTS = $(patsubst %.cpp, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.asm")
S_OBJECTS = $(patsubst %.asm, %.o, $(S_SOURCES))
OBJECTS = $(C_OBJECTS) $(S_OBJECTS)

C_FLAGS = -c -Wall -m32 -ggdb -nostdinc -nostdlib -fno-builtin -fno-stack-protector -IDrivers/${ARCH} -I./ -O2
LD_FLAGS = -T scripts/linker.ld -m elf_i386 -no-builtin -nostdlib -O4
ASM_FLAGS = -f elf32 -g -F stabs

#----------------------------------------------------------------------------
# ● 一般目标
#----------------------------------------------------------------------------
all: Cryst.bin
run: all
	qemu-system-i386 -kernel Cryst.bin
debug: all
	qemu-system-i386 -kernel Cryst.bin -gdb tcp::1234 -S &
	sleep 1 # GDB要等QEMU就绪
	cgdb -x scripts/gdbinit
clean:
	rm -f ${C_OBJECTS} ${S_OBJECTS} Cryst.bin
.PHONY: all run clean

#----------------------------------------------------------------------------
# ● 通用目标
#----------------------------------------------------------------------------
.cpp.o: .c
	@echo 编译C++代码文件$<……
	$(CC) $(C_FLAGS) $< -o $@

#----------------------------------------------------------------------------
# ● 特定目标
#----------------------------------------------------------------------------
Drivers/${ARCH}/Boot/boot.o: Drivers/${ARCH}/Boot/boot.asm
	nasm ${ASM_FLAGS} $^ -o $@

Drivers/${ARCH}/Basic/KFunc.o: Drivers/${ARCH}/Basic/KFunc.asm
	nasm ${ASM_FLAGS} $^ -o $@

Cryst.bin: ${OBJECTS}
	${CCLD} ${LD_FLAGS} -o Cryst.bin -O2 $^

#----------------------------------------------------------------------------
# ● 最终目标
#----------------------------------------------------------------------------
build: Cryst.bin
	strip Cryst.bin
