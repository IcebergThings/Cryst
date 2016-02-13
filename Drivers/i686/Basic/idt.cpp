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
// ■ idt.cpp
//-----------------------------------------------------------------------------
//   i686基础驱动：IDT。
//=============================================================================

#include "Basic/idt.h"
#include "config.h"

#ifdef DEBUG
#include "Basic/debug.h"
#endif


void irq_handler(IDT::pt_regs *regs) {
#ifdef DEBUG
	debugputstring((char*) INTERFACE8024, (char*) "IRQ! ");
#endif
	// 发送中断结束信号给 PICs
	// 按照我们的设置，从 32 号中断起为用户自定义中断
	// 因为单片的 Intel 8259A 芯片只能处理 8 级中断
	// 故大于等于 40 的中断号是由从片处理的
	if (regs->int_no >= 40) {
		// 发送重设信号给从片
		IO::out8(0xA0, 0x20);
	}
	// 发送重设信号给主片
	IO::out8(0x20, 0x20);

	if (interrupt_handlers[regs->int_no]) {
		interrupt_handlers[regs->int_no] (regs);
	}
}

void isr_handler(IDT::pt_regs *regs)
{
	if (interrupt_handlers[regs->int_no]) {
#ifdef DEBUG
		debugputstring((char*) INTERFACE8024, (char*) "ISR! ");
#endif
		interrupt_handlers[regs->int_no] (regs);
	} else {
#ifdef DEBUG
		debugputstring((char*) INTERFACE8024, (char*) "Unhandled interrupt!");
#endif
	}
}

//---------------------------------------------------------------------------
// ● IDT门设定  （flag | 0x60为设置用户态）
//---------------------------------------------------------------------------
void IDT::idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
	idt_entries[num].base_lo = base & 0xFFFF;
	idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

	idt_entries[num].sel     = sel;
	idt_entries[num].always0 = 0;

	idt_entries[num].flags = flags;
}

//---------------------------------------------------------------------------
// ● IDT表设定
//---------------------------------------------------------------------------
void IDT::idt_set_gates()
{
	idt_set_gate( 0, (uint32_t)isr0,  0x08, 0x8E);
	idt_set_gate( 1, (uint32_t)isr1,  0x08, 0x8E);
	idt_set_gate( 2, (uint32_t)isr2,  0x08, 0x8E);
	idt_set_gate( 3, (uint32_t)isr3,  0x08, 0x8E);
	idt_set_gate( 4, (uint32_t)isr4,  0x08, 0x8E);
	idt_set_gate( 5, (uint32_t)isr5,  0x08, 0x8E);
	idt_set_gate( 6, (uint32_t)isr6,  0x08, 0x8E);
	idt_set_gate( 7, (uint32_t)isr7,  0x08, 0x8E);
	idt_set_gate( 8, (uint32_t)isr8,  0x08, 0x8E);
	idt_set_gate( 9, (uint32_t)isr9,  0x08, 0x8E);
	idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
	idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
	idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
	idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
	idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
	idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
	idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
	idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
	idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
	idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
	idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
	idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
	idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
	idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
	idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
	idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
	idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
	idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
	idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
	idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
	idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
	idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);

	idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E);
	idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E);
	idt_set_gate(34, (uint32_t)irq2, 0x08, 0x8E);
	idt_set_gate(35, (uint32_t)irq3, 0x08, 0x8E);
	idt_set_gate(36, (uint32_t)irq4, 0x08, 0x8E);
	idt_set_gate(37, (uint32_t)irq5, 0x08, 0x8E);
	idt_set_gate(38, (uint32_t)irq6, 0x08, 0x8E);
	idt_set_gate(39, (uint32_t)irq7, 0x08, 0x8E);
	idt_set_gate(40, (uint32_t)irq8, 0x08, 0x8E);
	idt_set_gate(41, (uint32_t)irq9, 0x08, 0x8E);
	idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8E);
	idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8E);
	idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8E);
	idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8E);
	idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8E);
	idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8E);

	// 180 将来用于实现系统调用
	idt_set_gate(180, (uint32_t)isr180, 0x08, 0x8E);
}

//---------------------------------------------------------------------------
// ● 注册一个中断处理函数
//---------------------------------------------------------------------------
void register_interrupt_handler(uint8_t n, IDT::interrupt_handler_t h) {
	interrupt_handlers[n] = h;
}

//---------------------------------------------------------------------------
// ● IDT初始化
//---------------------------------------------------------------------------
IDT::IDT() {
	// 重新映射 IRQ 表
	// 两片级联的 Intel 8259A 芯片
	// 主片端口 0x20 0x21
	// 从片端口 0xA0 0xA1

	// 初始化主片、从片
	// 0001 0001
	IO::out8(0x20, 0x11);
	IO::out8(0xA0, 0x11);

	// 设置主片 IRQ 从 0x20(32) 号中断开始
	IO::out8(0x21, 0x20);

	// 设置从片 IRQ 从 0x28(40) 号中断开始
	IO::out8(0xA1, 0x28);

	// 设置主片 IR2 引脚连接从片
	IO::out8(0x21, 0x04);

	// 告诉从片输出引脚和主片 IR2 号相连
	IO::out8(0xA1, 0x02);

	// 设置主片和从片按照 8086 的方式工作
	IO::out8(0x21, 0x01);
	IO::out8(0xA1, 0x01);

	// 设置主从片允许中断
	IO::out8(0x21, 0x0);
	IO::out8(0xA1, 0x0);

	//fillchar((uint8_t*)interrupt_handlers, sizeof(interrupt_handler_t) * 256, 0x00);
	//fillchar((uint8_t*)idt_entries, sizeof(idt_entry_t) * 256, 0x00);

	idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
	idt_ptr.base = (uint32_t)&idt_entries;

	idt_set_gates();

	// 更新芯片中IDT表
	idt_update((uint32_t)&idt_ptr);

	// 打开中断
	IO::sti();
}
