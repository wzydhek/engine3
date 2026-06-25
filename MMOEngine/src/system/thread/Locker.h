/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "Lockable.h"
#include "Mutex.h"
#include "ReadWriteLock.h"

namespace sys {
  namespace thread {

	  //use templates someday
	  class SCOPED_CAPABILITY Locker  {
		  Lockable* lockable;

	public:
		Locker(Locker&& locker);

		Locker(const Locker&) = delete;
		Locker& operator=(const Locker&) = delete;


		Locker(Lockable* lock) ACQUIRE(lock);

		Locker(Mutex* lock) ACQUIRE(lock);

		Locker(ReadWriteLock* lock) ACQUIRE(lock);

		Locker(Mutex* lock, Mutex* cross) ACQUIRE(lock);

		Locker(ReadWriteLock* lock, ReadWriteLock* cross) ACQUIRE(lock);

		Locker(ReadWriteLock* lock, Mutex* cross) ACQUIRE(lock);

		Locker(Mutex* lock, ReadWriteLock* cross) ACQUIRE(lock);

		Locker(Lockable* lock, Lockable* cross) ACQUIRE(lock);

		~Locker() RELEASE();

		void release() RELEASE();
	  };

  } // namespace thread
} //namespace sys

using namespace sys::thread;
