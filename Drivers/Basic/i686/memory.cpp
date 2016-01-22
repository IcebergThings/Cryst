//=============================================================================
// ■ memory.c
//-----------------------------------------------------------------------------
//   Driver > Basic > i686 > memory
//=============================================================================

#include "memory.h"

//---------------------------------------------------------------------------
// ● 将页表绑定入页目录
//---------------------------------------------------------------------------
void Memory::map_pages_to_dir(int page_id, uint32_t* page_tab, uint8_t flag) {
	page_directory[page_id] = ((uint32_t)page_tab) | flag;
}

//---------------------------------------------------------------------------
// ● 将内存绑定入页表 (KByte计数)
//---------------------------------------------------------------------------
void Memory::map_physical_to_page_tab(uint32_t* page_tab, uint8_t flag, uint32_t f, uint32_t t) {
	for(uint32_t i = f; i < t; i++)
	{
		page_tab[i] = (i * 0x1000) | flag; 
	}
}


//---------------------------------------------------------------------------
// ● 内存初始化
//---------------------------------------------------------------------------
Memory::Memory () {
	
	// Init paging ===================================================
	//set each entry to not present
	int j;
	for(j = 0; j < 1024; j++)
	{
		// This sets the following flags to the pages:
		//   Supervisor: Only kernel-mode can access them
		//   Write Enabled: It can be both read from and written to
		//   Not Present: The page table is not present
		page_directory[j] = 0x00000002;
	}
	
	// holds the physical address where we want to start mapping these pages to.
	// in this case, we want to map these pages to the very beginning of memory.
	// we will fill 512 entries in the table, mapping 1.5 megabytes
	// (lower memory 1M, kernel 512KByte)
	for(uint32_t i = 0; i < 384; i++)
	{
		// As the address is page aligned, it will always leave 12 bits zeroed.
		// Those bits are used by the attributes ;)
		kern_page_table[i] = (i * 0x1000) | SL_RW_P; 
	}
	
	// Put the Page Table in the Page Directory
	map_pages_to_dir(0, (uint32_t*)kern_page_table, SL_RW_P);
	
	// enable it
	asm volatile ("movl %%eax, %%cr3" :: "a" (&page_directory)); // load PDPT into CR3
	asm volatile ("movl %cr0, %eax; orl $0x80000000, %eax; movl %eax, %cr0;");
	
	return;
		// Use this return to return back to the kernel
}
