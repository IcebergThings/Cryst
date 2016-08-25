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
// ■ kernel.cpp
//-----------------------------------------------------------------------------
//   这个文件是干什么的？
//=============================================================================

#include "config.h"

#include "Basic/types.h"
#include "Basic/io.h"
#include "Basic/memory.h"
#include "Basic/idt.h"
#include "Basic/safe.h"
#include "Basic/timer.h"

#include "Basic/types.h"

// 调试用
#ifdef DEBUG
#include "Basic/debug.h"
#endif


//---------------------------------------------------------------------------
// ● Multiarch初始化
//---------------------------------------------------------------------------
void arch_init () {
	#ifdef DEBUG
		Init_Debug();
		kputs("In Kernel\r\n");
	#endif

	Init_Memory();
	#ifdef DEBUG
		kputs("Memory Initialized\r\n");
	#endif
	Init_IDT();
	#ifdef DEBUG
		kputs("IDT Initialized\r\n");
	#endif
	Init_Safe();
	#ifdef DEBUG
		kputs("Safe Module Initialized\r\n");
	#endif
	Init_Timer(200);
	#ifdef DEBUG
		kputs("Timer Initialized\r\n");
	#endif
	return;
}

//---------------------------------------------------------------------------
// ● 内核IDLE
//---------------------------------------------------------------------------
void idle () {
	asm volatile ("UD2");
	for (;;) {
		io_cpu_hlt ();	// 挂起
	}

	return;
}

//---------------------------------------------------------------------------
// ● 主程序
//---------------------------------------------------------------------------
void kernel_main() {
	arch_init ();
	idle ();
}
