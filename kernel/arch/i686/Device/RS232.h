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
// ■ RS232.h
//-----------------------------------------------------------------------------
//   i686设备驱动：RS232串口。
//=============================================================================

#include "config.h"

#ifndef INCLUDE_I686_RS232_H
#define INCLUDE_I686_RS232_H

#include "Basic/idt.h"
#include "Basic/io.h"
#include "config.h"

#define COM1 0x3f8

typedef struct _RS232_t {
	uint16_t rate;
	uint16_t rate_divisor;

	uint16_t port;
} RS232_t;

int RS232_is_transmit_empty(RS232_t* device);
void RS232_write_serial(RS232_t* device, char a);
//---------------------------------------------------------------------------
// ● 初始化
//---------------------------------------------------------------------------
void Init_RS232(RS232_t* device, uint16_t port, uint16_t rate);

#endif
