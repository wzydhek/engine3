/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "Heap.h"

namespace sys {
  namespace mm {

	class MemoryMappedFile : public Heap {
		const char* fileName;
		uint32 fileSize;

		int deviceFD;

	public:
		MemoryMappedFile(const char* name, uint32 size);

		void create();

	protected:
		void openDevice();
	};

} // namespace mm
} // namespace sys

using namespace sys::mm;
