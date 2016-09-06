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
// ■ safe.c
//-----------------------------------------------------------------------------
//   i686保护模块
//=============================================================================

#ifndef INCLUDE_SAFE_H
#define INCLUDE_SAFE_H

#include "Basic/idt.h"
#include "Basic/timer.h"
#include "config.h"

#ifdef DEBUG
#include "Basic/debug.h"
#endif

extern void fatal_halt();
extern void panic(pt_regs* regs);
extern void panic_text(char* str);

void Init_Safe();

#endif
