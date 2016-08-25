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
// ■ debug.h
//-----------------------------------------------------------------------------
//   i686基础驱动：调试。
//=============================================================================

#ifndef INCLUDE_DEBUG_H_
#define INCLUDE_DEBUG_H_

#include "config.h"
#include "Basic/types.h"
#include "Device/RS232.h"

#ifdef X86DEBUG

extern RS232_t debug_serial;

void kputc(char c);
void kputs(char* st);
//---------------------------------------------------------------------------
// ● X86 debug初始化
//---------------------------------------------------------------------------
void Init_Debug();

#endif
#endif
