/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "Heap.h"

namespace sys {
  namespace mm {

	class ProcessHeap : public Heap {
		int heapID;

	public:
		ProcessHeap();
		~ProcessHeap();

		void select();

	};

} // namespace mm
} // namespace sys

using namespace sys::mm;
