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
// ■ memory.cpp
//-----------------------------------------------------------------------------
//   i686基础驱动：内存。
//=============================================================================

#include "Basic/memory.h"

extern int KERNEL_CODE_END; // From linker.ld

//---------------------------------------------------------------------------
// ● 页表&页目录
//---------------------------------------------------------------------------
uint32_t volatile page_directory[1024] __attribute__((aligned(4096)));
uint32_t volatile kern_page_table[1024] __attribute__((aligned(4096)));
uint32_t mem_size, upper_mem, page_count;
uint8_t volatile *phy_c;

//---------------------------------------------------------------------------
// ● 将页表绑定入页目录
//---------------------------------------------------------------------------
void Memory_map_pages_to_dir(int page_id, uint32_t* page_tab, uint8_t flag) {
	page_directory[page_id] = ((uint32_t)page_tab) | flag;
}

//---------------------------------------------------------------------------
// ● 占有物理内存（页计数）
//---------------------------------------------------------------------------
bool Memory_AllocPhy(uint32_t page) {
	if (phy_c[page] != 0) {
		return false;
	} else {
		phy_c[page] = 1;
		return true;
	}
}

//---------------------------------------------------------------------------
// ● 释放物理内存（页计数）
//---------------------------------------------------------------------------
void Memory_ReleasePhy(uint32_t page) {
	phy_c[page] = 0;
}

//---------------------------------------------------------------------------
// ● 寻找连续空闲内存（页计数）
//   返回空闲内存区起点，0为未找到。
//   这个函数建议只用来寻找16k以下的段，除非之后把段最大精度改成不是16kb。
//---------------------------------------------------------------------------
uint32_t Memory_SearchFree() {
	// 反正也用不了lower memory，直接跳过那部分
	for(uint32_t i = 256; i <= page_count; i++) {
		if (phy_c[i]==0) {
			return i;
		}
	}
	return 0;
}

//---------------------------------------------------------------------------
// ● 将内存绑定入页表（页计数）
//---------------------------------------------------------------------------
void Memory_map_physical_to_page_tab(uint32_t* page_tab, uint8_t flag, uint32_t f, uint32_t t) {
	for(uint32_t i = f; i < t; i++) {
		page_tab[i] = (i * 0x1000) | flag;
		Memory_AllocPhy(i);
	}
}

extern multiboot_t *glb_mboot_ptr;

//---------------------------------------------------------------------------
// ● 内存初始化
//---------------------------------------------------------------------------
void Init_Memory () {

	// 初始操作
	upper_mem = glb_mboot_ptr->mem_upper;
	mem_size = upper_mem + 1024; // Upper memory + Lower (1024KB)
	page_count = mem_size >> 2;
	int kernel_end_page = (uint32_t)(&KERNEL_CODE_END) >> 12;
	int kernel_memory_end_page = kernel_end_page + (page_count >> 12 ) + 1;
	phy_c = (uint8_t*) &KERNEL_CODE_END;

	// 初始分页
	// 将每个entry设置为not present
	int j;
	for(j = 0; j < 1024; j++)
	{
		// This sets the following flags to the pages:
		//   Supervisor: Only kernel-mode can access them
		//   Write Enabled: It can be both read from and written to
		//   Not Present: The page table is not present
		page_directory[j] = 0x00000002;
	}
	for(uint32_t i = 0; i < page_count; i++) {
		phy_c[i] = 4;
	}
	phy_c[page_count + 1] = 0; // For safe

	// holds the physical address where we want to start mapping these pages to.
	// in this case, we want to map these pages to the very beginning of memory.
	// we will fill 512 entries in the table, mapping 1.5 megabytes
	// (lower memory 1M, kernel space and phy alloc space)
	// 第一页不映射，这样能捕捉NULL指针
	for(uint32_t i = 1; i < kernel_memory_end_page; i++) {
		// As the address is page aligned, it will always leave 12 bits zeroed.
		// Those bits are used by the attributes ;)
		kern_page_table[i] = (i << 12) | SL_RW_P;
	}
	for(uint32_t i = 0; i < kernel_memory_end_page; i++) {
		phy_c[i] = 0;
	}

	// Put the Page Table in the Page Directory
	Memory_map_pages_to_dir(0, (uint32_t*)kern_page_table, SL_RW_P);

	// 启用
	asm volatile ("movl %%eax, %%cr3" :: "a" (&page_directory)); // load PDPT into CR3
	asm volatile ("movl %cr0, %eax; orl $0x80000000, %eax; movl %eax, %cr0;");

	// 返回到内核中
	return;
}
