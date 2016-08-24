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
// ■ io.c
//-----------------------------------------------------------------------------
//   i686基础驱动：IO。
//=============================================================================

#include "io.h"

//---------------------------------------------------------------------------
// ● CPU 挂起
//---------------------------------------------------------------------------
void IO::cpu_hlt () {
	asm volatile ("hlt");
}

//---------------------------------------------------------------------------
// ● 向端口写8位数据
//---------------------------------------------------------------------------
void IO::out8(uint16_t port, uint8_t value)
{
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

//---------------------------------------------------------------------------
// ● 从端口读8位数据
//---------------------------------------------------------------------------
uint8_t IO::in8(uint16_t port)
{
	uint8_t ret;

	asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));

	return ret;
}

//---------------------------------------------------------------------------
// ● 打开中断
//---------------------------------------------------------------------------
void IO::sti()
{
	asm volatile ("sti");
}

//---------------------------------------------------------------------------
// ● 关闭中断
//---------------------------------------------------------------------------
inline void IO::cli()
{
	asm volatile ("cli");
}

