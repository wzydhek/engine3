/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/**
 * @author      : theanswer (theanswer@Victors-MacBook-Pro.local)
 * @file        : AtomicTime
 * @created     : Monday Oct 15, 2018 22:10:03 CEST
 */

#pragma once

#include "system/platform.h"

#ifndef PLATFORM_WIN
	#include <unistd.h>
#else
	#include <windows.h>
	#include <windef.h>
	#include <pthread.h>
#endif

#include <time.h>
#include "system/lang/String.h"
#include "system/lang/StringBuffer.h"
#include "system/lang/Long.h"
#include "system/lang/Time.h"
#include "system/io/StringTokenizer.h"
#include <atomic>
#include <chrono>

namespace sys {
  namespace lang {

	class AtomicTime : public Variable {
	public:
#if defined(PLATFORM_MAC) || defined(PLATFORM_WIN)
		enum ClockType {
			REAL_TIME,
			THREAD_TIME,
			PROCESS_TIME,
			MONOTONIC_TIME
		};
#else
		typedef clockid_t ClockType;

		const static ClockType REAL_TIME = CLOCK_REALTIME;
		const static ClockType THREAD_TIME = CLOCK_THREAD_CPUTIME_ID;
		const static ClockType PROCESS_TIME = CLOCK_PROCESS_CPUTIME_ID;
		const static ClockType MONOTONIC_TIME = CLOCK_MONOTONIC;
#endif
	private:
		std::atomic<struct timespec> ts;

		template<typename convert_clock_type = std::chrono::system_clock,
			typename convert_duration_type = std::chrono::nanoseconds>
		static timespec timepointToTimespec(const std::chrono::time_point<convert_clock_type, convert_duration_type>& tp) {
			using namespace std::chrono;

			auto secs = time_point_cast<seconds>(tp);
			auto ns = time_point_cast<nanoseconds>(tp) -
				time_point_cast<nanoseconds>(secs);

			struct timespec ts;

			ts.tv_sec = static_cast<decltype(ts.tv_sec)>(secs.time_since_epoch().count());
			ts.tv_nsec = static_cast<decltype(ts.tv_nsec)>(ns.count());

			return ts;
		}

		template<typename NowType>
		static auto convertTimePointToNanos(const NowType& now) {
			using namespace std::chrono;

			auto nanos = time_point_cast<nanoseconds>(now);
			auto epoch = nanos.time_since_epoch();
			auto val = duration_cast<nanoseconds>(epoch);

			return val.count();
		}

	public:
		explicit AtomicTime(ClockType type = REAL_TIME) {
			updateToCurrentTime(type);
		}

		explicit AtomicTime(uint32 seconds) {
			struct timespec ts;

			ts.tv_sec = seconds;
			ts.tv_nsec = 0;

			this->ts.store(ts, std::memory_order_relaxed);
		}

		AtomicTime(const AtomicTime& time);

		AtomicTime(const Time& time);

		bool toString(String& str) const;

		bool parseFromString(const String& str, int version = 0);

		bool toBinaryStream(ObjectOutputStream* stream);

		bool parseFromBinaryStream(ObjectInputStream* stream);

		void updateToCurrentTime(ClockType type = REAL_TIME);

		void addMiliTime(uint64 mtime);

		void addMikroTime(uint64 utime);

		void addNanoTime(uint64 ntime);

		AtomicTime& operator=(const AtomicTime& t);

		AtomicTime& operator=(const Time& t);

		AtomicTime& operator=(uint32 seconds);

		int compareTo(const AtomicTime& t) const;

		int compareTo(const Time& t) const;

		String getFormattedTime() const;

		String getFormattedTimeFull() const;

		int compareMiliTo(const Time& t) const;

		static uint64 currentNanoTime(ClockType type = REAL_TIME);

		bool isPast() const;

		bool isPresent() const;

		bool isFuture() const;

	protected:
		static void checkForOverflow(struct timespec& ts);

	public:
		// getters
		uint32 getTime() const;

		Time getTimeObject() const;

		uint64 getMiliTime() const;

		uint64 getMikroTime() const;

		uint64 getNanoTime() const;

		int64 miliDifference(Time& t) const;

		int64 miliDifference() const;
	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;
