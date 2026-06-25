/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "MultimapMemoryManager.h"
#include "Allocator.h"

namespace sys {
  namespace mm {

	class Heap : public Allocator {
	protected:
		MultimapMemoryManager* mmapManager;

		void* heapBase;
		size_t heapSize;
		int flags;
		off_t offset;

		Allocator* allocator = nullptr;

	public:
		Heap();

		~Heap();

		void create(size_t size);

		void* allocate(size_t size);
		void* reallocate(void* mem, size_t size);
		void free(void* mem);

		size_t sizeOf(void* mem);

		bool contains(void* mem);

		void setShared();
		void setPrivate();

		void setAnonymous();

		Allocator* getAllocator();
	};

} // namespace mm
} // namespace sys

using namespace sys::mm;
