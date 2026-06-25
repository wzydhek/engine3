/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/platform.h"
#include <pthread.h>

#ifndef PLATFORM_WIN
	#include <sys/time.h>
#endif

#include <errno.h>
#include "system/lang/Time.h"
#include "system/thread/Mutex.h"

namespace sys {
  namespace thread {

	class Condition {
		pthread_mutex_t cmutex;
		pthread_cond_t cond;

		int signalCount;
		int waiterCount;

	public:
		Condition();

		virtual ~Condition();

		void init();

		int wait(Mutex* m);

		int wait();

		int timedWait(Mutex* m, const Time* time);

		int timedWait(const Time* time);

		void signal(Mutex* m);

		void signal();

		void broadcast(Mutex* m);

		void broadcast();

	private:
		int doWait(pthread_mutex_t* mutex);

		int doTimedWait(pthread_mutex_t* mutex, const Time* time);

		void doSignal();

		void doBroadcast();
	};

  } // namespace thread
} //namespace sys

using namespace sys::thread;
