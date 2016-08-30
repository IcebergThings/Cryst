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

#ifndef INCLUDE_TASK_H
#define INCLUDE_TASK_H

#include "config.h"
#include "Basic/types.h"
#include "debug.h"

typedef volatile struct _task_t {
	uint32_t ds;		// 用于保存用户的数据段描述符
	uint32_t edi; 	// 从 edi 到 eax 由 pusha 指令压入
	uint32_t esi;
	uint32_t ebp;
	uint32_t esp;
	uint32_t ebx;
	uint32_t edx;
	uint32_t ecx;
	uint32_t eax;
	uint32_t eip;		// 以下由处理器自动压入
	uint32_t cs;
	uint32_t eflags;
	uint32_t useresp;
	uint32_t ss;
} task_t;

extern volatile void taskb();
extern volatile char stb[4096];

void create_task(task_t* model, void* stack, void* eip);

void dump_task(task_t* regs);

#endif
