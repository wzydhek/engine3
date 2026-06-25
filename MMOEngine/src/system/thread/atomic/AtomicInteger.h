/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/platform.h"
#include "system/lang/Variable.h"
#include "system/io/ObjectInputStream.h"
#include "system/io/ObjectOutputStream.h"
#include <atomic>

namespace sys {
  namespace thread {
	namespace atomic {

	class AtomicInteger : public Variable {
		std::atomic<uint32> value{0};

	public:
		AtomicInteger();

		AtomicInteger(uint32 val);

		AtomicInteger(const AtomicInteger& v);

		~AtomicInteger();

		AtomicInteger& operator=(const AtomicInteger& val);

		uint32 add(uint32 val);

		uint32 increment();

		uint32 postIncrement();

		uint32 decrement();

		uint32 postDecrement();

		uint32 compareAndSetReturnOld(uint32 oldval, uint32 newval);

		bool compareAndSet(uint32 oldval, uint32 newval);

		uint32 get(std::memory_order m = std::memory_order_relaxed) const;

		void set(uint32 val, std::memory_order m = std::memory_order_seq_cst);

		uint32 operator=(const uint32 val);

		bool operator==(const int val) const;

		operator uint32() const;

		bool toBinaryStream(sys::io::ObjectOutputStream* stream);

		bool parseFromBinaryStream(sys::io::ObjectInputStream* stream);
	};

	} // namespace atomic
  } // namespace thread
} //namespace sys

using namespace sys::thread::atomic;
