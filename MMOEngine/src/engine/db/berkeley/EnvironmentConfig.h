/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * EnvironmentConfig.h
 *
 *  Created on: 13/02/2010
 *      Author: victor
 */

#pragma once

#include "system/platform.h"
#include <db.h>

namespace engine {
  namespace db {
    namespace berkeley {

	class LockDetectMode {
	public:
		const static uint32 DEFAULT = DB_LOCK_DEFAULT;
		const static uint32 EXPIRE = DB_LOCK_EXPIRE;
		const static uint32 MAXLOCKS = DB_LOCK_MAXLOCKS;
		const static uint32 MAXWRITE = DB_LOCK_MAXWRITE;
		const static uint32 MINLOCKS = DB_LOCK_MINLOCKS;
		const static uint32 MINWRITE = DB_LOCK_MINWRITE;
		//const static uint32 NONE = DB_LOCK_NONE;
		const static uint32 OLDEST = DB_LOCK_OLDEST;
		const static uint32 RANDOM = DB_LOCK_RANDOM;
		const static uint32 YOUNGEST = DB_LOCK_YOUNGEST;
	};

	class EnvironmentConfig {
		uint32 environmentFlags;
		uint32 threadCount;
		uint32 lockDetectMode;
		bool logAutoRemove;
		bool mvcc = false;
		bool direct = false;
		int maxLogFileSize;

	public:
		static EnvironmentConfig DEFAULT;

	public:
		EnvironmentConfig();

		void setRegister(bool val);

		void setLockDown(bool lockDownToMemory);

		void setAllowCreate(bool allowCreate);

		void setInitializeLocking(bool initializeLocking);

		void setInitializeLogging(bool initializeLogging);

		void setRecover(bool recover);

		void setPrivate(bool val);

		void setLogAutoRemove(bool logAutoRemove);

		void setMaxLogFileSize(int maxLogFileSize);

		void setThreaded(bool threaded);

		void setLockDetectMode(uint32 mode);

		void setThreadCount(int count);

		void setTransactional(bool transactional);

		void setInitializeCache(bool initializeCache);

		void setMultiVersionConcurrencyControl(bool val);

		void setDirectAccess(bool val);

		bool isThreaded() const;

		uint32 getEnvironmentFlags() const;

		uint32 getThreadCount() const;

		uint32 getLockDetectMode() const;

		int getMaxLogFileSize() const;

		bool getLogAutoRemove() const;

		bool isDirectAccess() const;

		bool isMVCC() const;

	};

    } // namespace berkeley
  } // namespace db
} // namespace engine

using namespace engine::db::berkeley;
