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
#include "StdC++/std.h"

#ifdef X86DEBUG
#define INTERFACE8024 0xb8000
//---------------------------------------------------------------------------
// ● X86 debug字符放置 (放入interface)
//---------------------------------------------------------------------------
void debugputchar(void* interface, char c);
//---------------------------------------------------------------------------
// ● X86 debug字符串放置 (放入interface)
//---------------------------------------------------------------------------
void debugputstring(char* interface, char* st);
#endif

#endif
