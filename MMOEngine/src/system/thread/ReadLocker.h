/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * ReadReadLocker.h
 *
 *  Created on: 20/06/2012
 *      Author: victor
 */

#pragma once

#include "ReadWriteLock.h"

namespace sys {
  namespace thread {

	class SCOPED_CAPABILITY ReadLocker  {
		const ReadWriteLock* lockable;
	public:
		ReadLocker(ReadLocker&& locker);

		ReadLocker(const ReadWriteLock* lock) ACQUIRE_SHARED(lock);

	    ReadLocker(const ReadLocker&) = delete;
		ReadLocker& operator=(const ReadLocker&) = delete;

		~ReadLocker() RELEASE();

	public:
		void release() RELEASE();
	};

  } // namespace thread
} //namespace sys

using namespace sys::thread;
