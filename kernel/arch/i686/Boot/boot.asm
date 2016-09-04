;  Copyright 2016 Iceberg OS
;
;  Licensed under the Apache License, Version 2.0 (the "License");
;  you may not use this file except in compliance with the License.
;  You may obtain a copy of the License at
;
;      http://www.apache.org/licenses/LICENSE-2.0
;
;  Unless required by applicable law or agreed to in writing, software
;  distributed under the License is distributed on an "AS IS" BASIS,
;  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
;  See the License for the specific language governing permissions and
;  limitations under the License.
;==============================================================================
; ■ boot.asm
;------------------------------------------------------------------------------
;   i686基础驱动：boot.asm。
;==============================================================================

MBOOT_HEADER_MAGIC 	equ 	0x1BADB002 	; Multiboot 魔数，由规范决定的

MBOOT_PAGE_ALIGN 	equ 	1 << 0    	; 0 号位表示所有的引导模块将按页(4KB)边界对齐
MBOOT_MEM_INFO 		equ 	1 << 1    	; 1 号位通过 Multiboot 信息结构的 mem_* 域包括可用内存的信息
						; (告诉GRUB把内存空间的信息包含在Multiboot信息结构中)

; 定义我们使用的 Multiboot 的标记
MBOOT_HEADER_FLAGS 	equ 	MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO

; 域checksum是一个32位的无符号值，当与其他的magic域(也就是magic和flags)相加时，
; 要求其结果必须是32位的无符号值 0 (即magic + flags + checksum = 0)
MBOOT_CHECKSUM 		equ 	- (MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

; 符合Multiboot规范的 OS 映象需要这样一个 magic Multiboot 头

; Multiboot 头的分布必须如下表所示：
; ----------------------------------------------------------
; 偏移量  类型  域名        备注
;
;   0     u32   magic       必需
;   4     u32   flags       必需
;   8     u32   checksum    必需
;
; 我们只使用到这些就够了，更多的详细说明请参阅 GNU 相关文档
;-----------------------------------------------------------

;-----------------------------------------------------------------------------

[BITS 32]  	; 所有代码以 32-bit 的方式编译

section .multiboot

; 在代码段的起始位置设置符合 Multiboot 规范的标记

dd MBOOT_HEADER_MAGIC 			; GRUB 会通过这个魔数判断该映像是否支持
dd MBOOT_HEADER_FLAGS				; GRUB 的一些加载时选项，其详细注释在定义处
dd MBOOT_CHECKSUM						; 检测数值，其含义在定义处

[GLOBAL _start]							; 内核代码入口，此处提供该声明给 ld 链接器
[GLOBAL glb_mboot_ptr]			; 全局的 struct multiboot * 变量
[EXTERN kernel_main]				; 声明内核 C 代码的入口函数
[EXTERN STACK_TOP]					; 声明内核栈顶 (从linker.ld获取以节省体积)

section .text 							; 代码段从这里开始

_start:
	cli												; 此时还没有设置好保护模式的中断处理，要关闭中断
														; 所以必须关闭中断
	mov esp, STACK_TOP				; 设置内核栈地址
	mov ebp, 0								; 帧指针修改为 0
;	and esp, 0xFFFFFF					; 栈地址按照16字节对齐
	mov [glb_mboot_ptr], ebx 	; 将 ebx 中存储的指针存入全局变量

.fpu_probe:
	mov edx, cr0							; Start probe, get CR0
	and edx, FPU_T						; clear TS and EM to force fpu access
	mov cr0, edx							; store control word
	fninit										; load defaults to FPU
	fnstsw [.testword]				; store status word
	cmp word [.testword], 0		; compare the written status with the expected FPU state
	jne .nofpu								; jump if the FPU hasn't written anything (i.e. it's not there)
	jmp .hasfpu
.nofpu:
	hlt
	jmp .nofpu

CR0_TS	equ	001000b
CR0_EM	equ	000100b
FPU_T		equ (-1) - (CR0_TS + CR0_EM)

.testword: DW 0x55AA				; store garbage to be able to detect a change
.hasfpu:
;	mov edx, cr0
;	xor edx, (CR0_EM | CR0_TS); clear TS and EM to force fpu access
;	mov cr0, edx

	jmp kernel_main						; 调用内核入口函数
.end:

;-----------------------------------------------------------------------------

section .bss								; 未初始化的数据段从这里开始
glb_mboot_ptr:							; 全局的 multiboot 结构体指针
	resb 4

;-----------------------------------------------------------------------------
