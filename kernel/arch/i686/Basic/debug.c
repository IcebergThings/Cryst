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
// ■ debug.cpp
//-----------------------------------------------------------------------------
//   Drivers > i686 > Basic > debug
//=============================================================================

#include "debug.h"

RS232_t serial_debug;

void kputc(char c) {
	RS232_write_serial(&serial_debug, c);
}

void kputs(char* st) {
	char* s = st;
	while (*s) kputc(*s++);
}

//---------------------------------------------------------------------------
// ● X86 debug初始化
//---------------------------------------------------------------------------
void Init_Debug() {
	Init_RS232(&serial_debug, COM1);
}
