//=============================================================================
// ■ kernel.c
//-----------------------------------------------------------------------------
//   这个文件用来初始化不同arch
//=============================================================================

#ifndef INCLUDE_ARCH_INIT_H
#define INCLUDE_ARCH_INIT_H

#include "Drivers/Basic/i686/memory.h"
#include "Drivers/Basic/i686/types.h"
#include "Drivers/Basic/i686/io.h"

void arch_init () {
	
#ifdef i686
	memory_init ();
#endif
	
	return;
}

#endif