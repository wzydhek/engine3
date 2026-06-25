/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
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

	class AllocationTracker : public AllocationHook {
		static AllocationTracker* instance;

		Allocator* realAllocator;

		struct MM_Allocator
		{
			unsigned long caller;
			long          total;
		};

		unsigned int numOfAllocatorsM ;

		MM_Allocator allocatorsM[MM_ALLOCATOR_LIST_SIZE];

		uint64 protectedPages[5000];
		int protectedPagesCount;

		Time nextAllocatorPrint;

		AllocationTracker();

		~AllocationTracker();

	public:
		static AllocationTracker* getInstance();

		bool isProtected(uintptr_t page);

		void* onAllocate(size_t size, const void* allocator);
		void onFree(void* ptr, const void*);
		void* onReallocate(void* ptr, size_t size, const void* alloc);

		void setAllocator(Allocator* alloc);

	protected:
		size_t sizeOfPointer(void* ptr);

		void updateAllocatorList(unsigned long allocator, long size);

		void print();

		void addOverWriteProtector(void* ptr, size_t size);
	};

  } // namespace mm
} // namespace sys

using namespace sys::mm;
