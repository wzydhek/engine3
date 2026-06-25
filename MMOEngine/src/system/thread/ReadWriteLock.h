/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "Lockable.h"

namespace sys {
  namespace thread {

	class Mutex;

	class CAPABILITY("mutex") ReadWriteLock : public Lockable  {
	protected:
		pthread_rwlock_t rwlock;

	public:
		ReadWriteLock();

		ReadWriteLock(const String& s);

		ReadWriteLock(const ReadWriteLock& s);

		ReadWriteLock& operator=(const ReadWriteLock& lock);

		~ReadWriteLock();

		void lock(bool doLock = true) ACQUIRE();

		virtual void rlock(bool doLock = true) ACQUIRE_SHARED();

		virtual void wlock(bool doLock = true) ACQUIRE();
		virtual void wlock(Mutex* lock) ACQUIRE();
		virtual void wlock(ReadWriteLock* lock) ACQUIRE();
		virtual void rlock(ReadWriteLock* lock) ACQUIRE_SHARED();
		virtual void rlock(Lockable* lock)  ACQUIRE_SHARED();

		void lock(Lockable* lockable) ACQUIRE();

		void lock(ReadWriteLock* lockable) ACQUIRE();

		void lock(Mutex* lockable) ACQUIRE();

		bool tryWLock() TRY_ACQUIRE(true);

		void unlock(bool doLock = true) RELEASE();

		virtual void runlock(bool doLock = true) RELEASE_SHARED();

		bool destroy();

		friend class Condition;
	};

  } // namespace thread
} //namespace sys

using namespace sys::thread;
