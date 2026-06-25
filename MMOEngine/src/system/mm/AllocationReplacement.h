/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * AllocationReplacement.h
 *
 *  Created on: 23/12/2011
 *      Author: victor
 */

#pragma once

#include "system/lang/Time.h"
#include "system/thread/Mutex.h"
#include "system/thread/Locker.h"
#include "system/util/VectorSet.h"
#include "Allocator.h"
#include "AllocationHook.h"
#include "Heap.h"

#define MM_ALLOCATOR_LIST_SIZE 4096

namespace sys {
  namespace mm {
  	  class AllocationReplacement : public AllocationHook {
  		static AllocationReplacement* instance;

  		Allocator* realAllocator;
  	  public:
		AllocationReplacement();

  		void* onAllocate(size_t size, const void* allocator);
  		void onFree(void* ptr, const void*);
  		void* onReallocate(void* ptr, size_t size, const void* alloc);

  		static AllocationReplacement* getInstance();

  		void setRealAllocator(Allocator* allocator);
  	  };

  }
}

using namespace sys::mm;
