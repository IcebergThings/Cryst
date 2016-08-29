// Copyright 2016 Iceberg OS
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=============================================================================
// ■ safe.c
//-----------------------------------------------------------------------------
//   i686保护模块
//=============================================================================

#include "safe.h"

/*extern void isr1(); 		// 1 #DB 调试异常
extern void isr2(); 		// 2 NMI
extern void isr3(); 		// 3 BP 断点异常
extern void isr4(); 		// 4 #OF 溢出
extern void isr5(); 		// 5 #BR 对数组的引用超出边界
extern void isr7(); 		// 7 #NM 设备不可用(无数学协处理器)
extern void isr8(); 		// 8 #DF 双重故障(有错误代码)
extern void isr9(); 		// 9 协处理器跨段操作
extern void isr10(); 		// 10 #TS 无效TSS(有错误代码)
extern void isr11(); 		// 11 #NP 段不存在(有错误代码)
extern void isr13(); 		// 13 #GP 常规保护(有错误代码)
extern void isr15(); 		// 15 CPU 保留
extern void isr17(); 		// 17 #AC 对齐检查
extern void isr18(); 		// 18 #MC 机器检查
extern void isr19(); 		// 19 #XM SIMD(单指令多数据)浮点异常*/

// #DE 除 0 异常
static void isr0_handler(pt_regs *regs) {
	kprintf("Divide by 0 - #DE, at EIP=0x%x\r\n", regs->eip);
}

// #UD 无效或未定义的操作码
static void isr6_handler(pt_regs *regs) {
	kprintf("Undefined - #UD, at EIP=0x%x\r\n", regs->eip);

	io_cpu_hlt();
}

// #SS 栈错误(有错误代码)
static void isr12_handler(pt_regs *regs) {
	kprintf("Stack Error - #SS, ERR CODE=0x%x, at EIP=0x%x\r\n", regs->err_code, regs->eip);
}

// #GP 常规保护(有错误代码)
static void isr13_handler(pt_regs *regs) {
	kprintf("General Protection - #GP, ERR CODE=0x%x, at EIP=0x%x\r\n", regs->err_code, regs->eip);
}

// #PF 页故障(有错误代码)
static void isr14_handler(pt_regs *regs) {
	kprintf("Page fault - #PF, ERR CODE=0x%x, at EIP=0x%x\r\n", regs->err_code, regs->eip);
}

// #MF 浮点处理单元错误
static void isr16_handler(pt_regs *regs) {
	kprintf("Float Fault - #MF, at EIP=0x%x\r\n", regs->eip);
}

void Init_Safe() {
	idt_register_interrupt_handler(0, isr0_handler);
	idt_register_interrupt_handler(6, isr6_handler);
	idt_register_interrupt_handler(12, isr12_handler);
	idt_register_interrupt_handler(13, isr13_handler);
	idt_register_interrupt_handler(14, isr14_handler);
	idt_register_interrupt_handler(16, isr16_handler);
}
