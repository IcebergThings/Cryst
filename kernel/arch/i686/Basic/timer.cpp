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
// ■ Timer.cpp
//-----------------------------------------------------------------------------
//   i686基础驱动：Timer。
//=============================================================================

#include "Basic/timer.h"

//---------------------------------------------------------------------------
// ● 时钟信号处理函数
//---------------------------------------------------------------------------
static RS232 serial;
static uint64_t tick = 0;
static void timer_callback(IDT::pt_regs *regs) {
	tick++;
#ifdef DEBUG
	serial.write_serial('T');
	debugputstring((char*) INTERFACE8024, (char*) "Timer Call back ");
#endif
}


//---------------------------------------------------------------------------
// ● 时钟初始化
//---------------------------------------------------------------------------
Timer::Timer(uint32_t frequency) {

	// 注册时间相关的处理函数
	register_interrupt_handler(IRQ0, timer_callback);

	// Intel 8253/8254 PIT芯片 I/O端口地址范围是40h~43h
	// 输入频率为 1193180 (12MHz)，frequency 即每秒中断次数
	uint32_t divisor = 1193180 / frequency;

	// D7 D6 D5 D4 D3 D2 D1 D0
	// 0  0  1  1  0  1  1  0
	// 即就是 36 H
	// 设置 8253/8254 芯片工作在模式 3 下
	IO::out8(0x43, 0x36);

	// 拆分低字节和高字节
	uint8_t low = (uint8_t)(divisor & 0xFF);
	uint8_t hign = (uint8_t)((divisor >> 8) & 0xFF);

	// 分别写入低字节和高字节
	IO::out8(0x40, low);
	IO::out8(0x40, hign);
}
