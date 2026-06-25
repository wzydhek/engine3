/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/platform.h"

#ifndef PLATFORM_WIN
	#include <unistd.h>
	#include <cstdio>
	#include <ctime>
#else
	#include <windows.h>
	#include <windef.h>
	#include <pthread.h>
	#include <ctime>

	static int conv_num(const char** buf, int* dest, int llim, int ulim);
	char* strptime(const char* buf, const char* fmt, struct tm* tm);

#endif

#include "String.h"
#include "StringBuffer.h"
#include "Long.h"
#include <chrono>

namespace sys {
  namespace lang {

	class Time {
	public:
#if defined(PLATFORM_WIN) || defined(PLATFORM_MAC)
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
		struct timespec ts;

		template<typename convert_clock_type,
			typename convert_duration_type>
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
		explicit Time(ClockType type = REAL_TIME) noexcept {
			updateToCurrentTime(type);
		}

		explicit Time(uint32 seconds) noexcept {
			ts.tv_sec = seconds;
			ts.tv_nsec = 0;
		}

		Time(const Time& time);

		bool toString(String& str) const;

		bool parseFromString(const String& str, int version = 0);

		bool toBinaryStream(ObjectOutputStream* stream);

		bool parseFromBinaryStream(ObjectInputStream* stream);

		void updateToCurrentTime(ClockType type = REAL_TIME);

		void addMiliTime(uint64 mtime);

		void addMikroTime(uint64 utime);

		void addNanoTime(uint64 ntime);

		Time& operator=(const Time& t);

		Time& operator=(uint32 seconds);

		int compareTo(const Time& t) const;

		String getFormattedTime() const;

		String getFormattedTimeShort() const;

		String getFormattedTimeFull(bool include_ms = true) const;

		String getFormattedTime(const String& format) const;

		int compareMiliTo(const Time& t) const;

		static Time fromISO8601(const String& isoString);

		static uint64 currentNanoTime(ClockType type = REAL_TIME);

		bool isPast() const;

		bool isPresent() const;

		bool isFuture() const;

	protected:
		void checkForOverflow();

	public:
		// getters
		uint32 getTime() const;

		uint64 getMiliTime() const;

		uint64 getMikroTime() const;

		uint64 getNanoTime() const;

		int64 miliDifference(const Time& t) const;

		int64 miliDifference(ClockType type = REAL_TIME) const;

		struct timespec* getTimeSpec();

		const struct timespec* getTimeSpec() const;

		friend class AtomicTime;

	};

	class SerializableTime : public Time, public Variable {
	public:

		SerializableTime();

		SerializableTime(const SerializableTime& time);

		SerializableTime& operator=(const SerializableTime& time);

		SerializableTime& operator=(const Time& time);

		bool parseFromBinaryStream(ObjectInputStream* stream);

		bool toBinaryStream(ObjectOutputStream* stream);


	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;
