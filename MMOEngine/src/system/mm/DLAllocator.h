/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/platform.h"

#ifndef PLATFORM_WIN

	#include "Allocator.h"

	namespace sys {
	namespace mm {

		class DLAllocator : public Allocator {
			void* dlBase;
			size_t dlSize;

			void* dlMspace;

		public:
			DLAllocator(void* base, size_t size);

			~DLAllocator();

			void initialize();

			void destroy();

			void* allocate(size_t size);

			void* reallocate(void* mem, size_t newsize);

			void free(void* mem);

			size_t sizeOf(void* mem);
		};

	} // namespace mm
	} // namespace sys

	using namespace sys::mm;

#endif
