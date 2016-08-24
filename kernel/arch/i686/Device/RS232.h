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

#ifdef DEBUG
#include "Basic/debug.h"
#endif

#define PORT 0x3f8   /* COM1 */

class RS232 {

private:
	void init_serial();
	int is_transmit_empty();

public:
	void write_serial(char a);
	//---------------------------------------------------------------------------
	// ● 初始化
	//---------------------------------------------------------------------------
	RS232();
};

#endif
