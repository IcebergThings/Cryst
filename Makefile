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
CC = clang
AS = nasm
CCLD = ld
ARCH = i686

C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.asm")
S_OBJECTS = $(patsubst %.asm, %.o, $(S_SOURCES))
OBJECTS = $(C_OBJECTS) $(S_OBJECTS)

CFLAGS = -c -std=gnu11 -Wall -Wextra -m32 -ggdb -O3 \
	-nostdinc -fno-builtin -fno-stack-protector \
	-Ikernel -Ikernel/arch/$(ARCH)
LDFLAGS = -T scripts/linker.ld -melf_i386 -no-builtin -nostdlib -O4
ASFLAGS = -f elf32 -g -F stabs
VMFLAGS = --cpu coreduo -kernel Cryst.bin

#----------------------------------------------------------------------------
# ● 一般目标
#----------------------------------------------------------------------------
all: Cryst.bin
run: all
	qemu-system-i386 $(VMFLAGS)
debug: all
	qemu-system-i386 $(VMFLAGS) -gdb tcp::1234 -S &
	sleep .5 # GDB要等QEMU就绪
	cgdb -x scripts/gdbinit
clean:
	rm -f $(C_OBJECTS) $(S_OBJECTS) Cryst.bin
.PHONY: all run clean

#----------------------------------------------------------------------------
# ● 通用目标
#----------------------------------------------------------------------------
.c.o: .c
	@echo 编译C++代码文件$^……
	$(CC) $(CFLAGS) $^ -o $@

#----------------------------------------------------------------------------
# ● 特定目标
#----------------------------------------------------------------------------
kernel/arch/$(ARCH)/Boot/boot.o: kernel/arch/$(ARCH)/Boot/boot.asm
	$(AS) $(ASFLAGS) $^ -o $@

kernel/arch/$(ARCH)/Basic/KFunc.o: kernel/arch/$(ARCH)/Basic/KFunc.asm
	$(AS) $(ASFLAGS) $^ -o $@

Cryst.bin: $(OBJECTS)
	$(CCLD) $(LDFLAGS) -o Cryst.bin $^

#----------------------------------------------------------------------------
# ● 最终目标
#----------------------------------------------------------------------------
build: Cryst.bin
	@echo Can not perform build now
#	strip Cryst.bin
