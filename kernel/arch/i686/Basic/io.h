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
// ■ io.h
//-----------------------------------------------------------------------------
//   i686基础驱动：IO。
//=============================================================================

#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

#include "Basic/types.h"

//---------------------------------------------------------------------------
// ● CPU 挂起
//---------------------------------------------------------------------------
void io_cpu_hlt();
//---------------------------------------------------------------------------
// ● 向端口写8bit数据
//---------------------------------------------------------------------------
void io_out8(uint16_t port, uint8_t value);
//---------------------------------------------------------------------------
// ● 从端口读8bit数据
//---------------------------------------------------------------------------
uint8_t io_in8(uint16_t port);
//---------------------------------------------------------------------------
// ● 打开中断
//---------------------------------------------------------------------------
void io_sti();
//---------------------------------------------------------------------------
// ● 关闭中断
//---------------------------------------------------------------------------
void io_cli();

#endif
