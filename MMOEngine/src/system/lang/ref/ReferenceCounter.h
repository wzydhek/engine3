/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include <signal.h>
#include "system/platform.h"
#include "system/lang/System.h"
#include <atomic>

namespace sys {
  namespace lang {

	class ReferenceCounter {
	protected:
		std::atomic<uint32> _references{0};

	public:
		ReferenceCounter();

		ReferenceCounter(uint32 count);

		ReferenceCounter(const ReferenceCounter& counter);

		ReferenceCounter& operator=(const ReferenceCounter& counter);

	public:
		uint32 increaseCount() volatile;

		void setLowestBit() volatile;

		void clearLowestBit() volatile;

		bool tryFinalDecrement() volatile;

		uint32 decrementAndTestAndSet() volatile;

		uint32 getReferenceCount(std::memory_order o = std::memory_order_consume) volatile const;

		void reset() volatile;

	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;
