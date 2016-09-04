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
// ■ Task.h
//-----------------------------------------------------------------------------
//   i686任务
//=============================================================================

#include "task.h"

extern task_t* sttaskb;

void taskb() {
	for (;;) kputc('B');
}

volatile char stb[4096];

volatile void create_task(task_t* model, void* stack_top, void* eip) {
	kprintf("New task, esp=0x%x\r\n", stack_top);
	volatile task_t* t = (task_t*) (stack_top - sizeof(task_t));
	t->ds = model->ds;
	t->edi = 0x0; 	// 从 edi 到 eax 由 pusha 指令压入
	t->esi = 0x0;
	t->ebp = 0x0;
	t->esp = (uint32_t) t - 20;
	kprintf("task->esp=%x\r\n", t->esp);
	t->ebx = 0x0;
	t->edx = 0x0;
	t->ecx = 0x0;
	t->eax = 0x0;
	t->eip = (uint32_t) eip;		// 以下由处理器自动压入
	kprintf("task->eip=%x\r\n", t->eip);
	t->cs = model->cs;
	t->eflags = model->eflags;
	t->useresp = stack_top;
	kprintf("task->useresp=%x\r\n", t->useresp);
	t->ss = model->ss;
}

void dump_task(task_t* regs) {
	kprintf("Dump task, esp=0x%x\r\n", regs);
	kprintf("ds=0x%x\r\n", regs->ds);
	kprintf("edi=0x%x\r\n", regs->edi);
	kprintf("esi=0x%x\r\n", regs->esi);
	kprintf("ebp=0x%x\r\n", regs->ebp);
	kprintf("esp=0x%x\r\n", regs->esp);
	kprintf("ebx=0x%x\r\n", regs->ebx);
	kprintf("edx=0x%x\r\n", regs->edx);
	kprintf("ecx=0x%x\r\n", regs->ecx);
	kprintf("eax=0x%x\r\n", regs->eax);
	kprintf("eip=0x%x\r\n", regs->eip);
	kprintf("cs=0x%x\r\n", regs->cs);
	kprintf("eflags=0x%x\r\n", regs->eflags);
	kprintf("useresp=0x%x\r\n", regs->useresp);
	kprintf("ss=0x%x\r\n", regs->ss);
}
