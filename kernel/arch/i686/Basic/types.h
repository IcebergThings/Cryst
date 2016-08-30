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
// ■ types.h
//-----------------------------------------------------------------------------
//   类型定义→图方便
//=============================================================================

#ifndef INCLUDE_TYPES_H_
#define INCLUDE_TYPES_H_

#ifndef NULL
	#define NULL ((void*) 0)
#endif

typedef unsigned long  uint64_t;
typedef   signed long  int64_t;
typedef unsigned int   uint32_t;
typedef   signed int   int32_t;
typedef unsigned short uint16_t;
typedef   signed short int16_t;
typedef unsigned char  uint8_t;
typedef   signed char  int8_t;
typedef unsigned int   size_t;
typedef   signed int   intptr_t;
typedef unsigned int   uintptr_t;

typedef int8_t bool;
#if !(defined(true) && defined(false))
	#define true ((bool) 1)
	#define false ((bool) 0)
#endif

// 我们的征途是……
// http://en.cppreference.com/w/c/types/integer

#endif 	// INCLUDE_TYPES_H_
