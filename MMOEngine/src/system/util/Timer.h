/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang/Time.h"
#include "system/lang/Function.h"
#include "system/lang/Runnable.h"

namespace sys {
	namespace util {

		class Timer {
			uint64 startTime = 0;
			uint64 elapsedTime = 0;

			uint64 totalTime = 0;

			Time::ClockType clockType = Time::MONOTONIC_TIME;

		public:
			explicit Timer(Time::ClockType type) : clockType(type) {
			}

			Timer() = default;
			Timer(const Timer& timer) = default;

			Timer& operator=(const Timer& timer) = default;

			uint64 run(const sys::lang::Function<void()>& function);

			uint64 run(Runnable* runnable);

			void start();

			uint64 stop();

			void clear();

			uint64 stopMs();

			uint64 elapsedToNow() const;

			uint64 elapsedMs() const;

			uint64 getStartTime() const;

			uint64 getElapsedTime() const;

			uint64 getTotalTime() const;

			uint64 getStartTimeMs() const;

			uint64 getElapsedTimeMs() const;

			uint64 getTotalTimeMs() const;

			Time::ClockType getClockType() const;
		};

	} // namespace util
} // namespace sys

using namespace sys::util;
