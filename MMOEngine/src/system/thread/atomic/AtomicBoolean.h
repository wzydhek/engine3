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

	class AtomicBoolean : public Variable {
		std::atomic<bool> value{false};

	public:
		AtomicBoolean();

		AtomicBoolean(bool val);

		AtomicBoolean(AtomicBoolean&& val);

		AtomicBoolean(const AtomicBoolean& val);

		~AtomicBoolean();

		bool compareAndSet(bool oldval, bool newval);

		bool get(std::memory_order m = std::memory_order_relaxed) const;

		void set(bool val, std::memory_order m = std::memory_order_relaxed);

		AtomicBoolean& operator=(const bool val);

		bool operator==(const bool val) const;

		operator bool() const;

		bool toBinaryStream(sys::io::ObjectOutputStream* stream) NO_THREAD_SAFETY_ANALYSIS;

		bool parseFromBinaryStream(sys::io::ObjectInputStream* stream) NO_THREAD_SAFETY_ANALYSIS;
	};

	} // namespace atomic
  } // namespace thread
} //namespace sys

using namespace sys::thread::atomic;
