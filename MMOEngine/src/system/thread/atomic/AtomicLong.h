/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/platform.h"
#include "system/io/ObjectInputStream.h"
#include "system/io/ObjectOutputStream.h"
#include <atomic>

namespace sys {
  namespace thread {
	namespace atomic {

	class AtomicLong {
		std::atomic<uint64> value{0};

	public:
		AtomicLong();

		AtomicLong(uint64 val);

		AtomicLong(const AtomicLong& val);

		AtomicLong& operator=(const AtomicLong& v);

		AtomicLong& operator=(const uint64 val);

		uint64 increment();

		uint64 decrement();

		uint64 add(uint64 val);

		uint64 compareAndSetReturnOld(uint64 oldval, uint64 newval);

		bool compareAndSet(uint64 oldval, uint64 newval);

		uint64 get() const;

		void set(uint64 val);

		operator uint64() const;

		bool operator==(const uint64 val) const;

		bool toBinaryStream(sys::io::ObjectOutputStream* stream);

		bool parseFromBinaryStream(sys::io::ObjectInputStream* stream);
	};

	} // namespace atomic
  } // namespace thread
} //namespace sys

using namespace sys::thread::atomic;
