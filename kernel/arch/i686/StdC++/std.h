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
// ■ std.h
//-----------------------------------------------------------------------------
//   Driver > Basic > StdC++ > std
//=============================================================================

#ifndef INCLUDE_STD_H
#define INCLUDE_STD_H

#include "Basic/types.h"

//---------------------------------------------------------------------------
// ● 标准C函数：内存复制
//---------------------------------------------------------------------------
void* memcpy(void *desc, const void * src, size_t size);

//---------------------------------------------------------------------------
// ● 标准C函数：内存比较（字符串比较）
//---------------------------------------------------------------------------
int my_memcmp(const void *buffer1,const void *buffer2,int count);

//---------------------------------------------------------------------------
// ● 来自Pascal的函数：内存填充
//---------------------------------------------------------------------------
void fillchar(uint8_t* mem, size_t size, uint8_t pattern);

#endif
