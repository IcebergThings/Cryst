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
// ■ memory.h
//-----------------------------------------------------------------------------
//   i686基础驱动：内存。
//=============================================================================

#ifndef INCLUDE_MEMORY_H_
#define INCLUDE_MEMORY_H_

#include "Basic/types.h"
#include "Basic/multiboot.h"

#define SL_RW_P 3 // attributes: supervisor level, read/write, present.

class Memory {
	public:
	//---------------------------------------------------------------------------
	// ● 页表&页目录
	//---------------------------------------------------------------------------
	uint32_t volatile page_directory[1024] __attribute__((aligned(4096)));
	uint32_t volatile kern_page_table[1024] __attribute__((aligned(4096)));
	uint32_t mem_size, upper_mem, page_count;
	uint8_t volatile *phy_c;
	// 0 1 4 8 256 -> 0 4 16 32 1024

	//---------------------------------------------------------------------------
	// ● 占有物理内存(页计数)
	//---------------------------------------------------------------------------
	bool AllocPhy(uint32_t page);
	//---------------------------------------------------------------------------
	// ● 释放物理内存(页计数)
	//---------------------------------------------------------------------------
	void ReleasePhy(uint32_t page);
	//---------------------------------------------------------------------------
	// ● 寻找连续空闲内存(页计数) - 返回空闲内存区起点 - 0为未找到
	//---------------------------------------------------------------------------
	uint32_t SearchFree();
	//---------------------------------------------------------------------------
	// ● 将页表绑定入页目录
	//---------------------------------------------------------------------------
	void map_pages_to_dir(int page_id, uint32_t* page_tab, uint8_t flag);
	//---------------------------------------------------------------------------
	// ● 将内存绑定入页表 (KByte计数)
	//---------------------------------------------------------------------------
	void map_physical_to_page_tab(uint32_t* page_tab, uint8_t flag, uint32_t f, uint32_t t);
	//---------------------------------------------------------------------------
	// ● 内存初始化
	//---------------------------------------------------------------------------
	Memory();
};

#endif
