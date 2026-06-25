/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/platform.h"
#include <pthread.h>
#include "system/lang/String.h"
#include "system/lang/StackTrace.h"
#include "system/lang/Time.h"
#include "atomic/AtomicInteger.h"
#include "atomic/AtomicReference.h"
#include "Thread.h"

#ifndef TRACE_REFERENCES
	#define TRACE_BLOCK_TIME
#endif

//namespace sys {
//  namespace lang {
//	  class Time;
//  }
//}

namespace sys {
  namespace thread {

	class Mutex;

	class CAPABILITY("mutex") Lockable {
	protected:
		//String lockName;

		AtomicReference<Thread*> threadLockHolder;
		AtomicInteger readLockCount;

#ifdef TRACE_LOCKS
		StackTrace* trace;
		StackTrace* unlockTrace;

		Time lockTime;

		bool doTrace;
#endif

#ifdef LOG_LOCKS
		AtomicInteger lockCount;
		int currentCount;

		bool doLog;
#endif

	public:
		Lockable();
		Lockable(const String& s);

		virtual ~Lockable();

		ACQUIRE() virtual void lock(bool doLock = true) = 0;
		ACQUIRE() virtual void lock(Lockable* lockable) = 0;

		RELEASE() virtual void unlock(bool doLock = true) = 0;

	protected:
		uint64 lockAcquiring(const char* modifier = "");

		uint64 lockAcquiring(Lockable* lockable, const char* modifier = "");

		uint64 lockAcquired(const char* modifier = "");

		uint64 lockAcquired(Lockable* lockable, const char* modifier = "");

		void lockReleasing(const char* modifier = "");

		void lockReleased(const char* modifier = "");

		void traceDeadlock(const char* modifier = "");

		void refreshTrace();

		void deleteTrace();

		void refreshUnlockTrace();

		void deleteUnlockTrace();

		void clearCurrentLockHolder();

		void setCurrentLockHolder(Thread* thread);

	public:
		bool isLockedByCurrentThread() const;

		bool isReadLocked() const;

		Thread* getLockHolderThread();

		// setters
		void setLockName(const String& s);

		void setLockLogging(bool dolog);

		void setLockTracing(bool tracing);
	};

  } // namespace thread
} //namespace sys

using namespace sys::thread;
