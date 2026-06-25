/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include <sys/times.h>
#include "system/platform.h"

namespace sys {
  namespace util {

    class TickTimer {
    	struct tms startTicks;
    	struct tms elapsedTicks;

    public:
		TickTimer();

    	void start();

    	void stop();

    	uint64 elapsedUserTicks() const;

    	uint64 elapsedSystemTicks() const;

    	void clearStartTicks();

    	void clearElapsedTicks();

    	static uint64 getTicksPerSec();

    };

  } // namespace util
} // namespace sys

using namespace sys::util;
