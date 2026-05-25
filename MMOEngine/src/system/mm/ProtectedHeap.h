/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "Heap.h"

namespace sys {
  namespace mm {

	class ProtectedHeap : public Heap {
		volatile unsigned protectionLevel;

	public:
		ProtectedHeap();

		void protect();
		void unprotect();

	};

} // namespace mm
} // namespace sys

using namespace sys::mm;
