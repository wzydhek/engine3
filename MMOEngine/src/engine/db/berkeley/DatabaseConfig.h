/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * DatabaseConfig.h
 *
 *  Created on: 13/02/2010
 *      Author: victor
 */

#pragma once

#include <db.h>
#include "system/platform.h"

namespace engine {
  namespace db {
    namespace berkeley {

	class LockMode {
	public:
		const static uint32 DEFAULT = 0;
		const static uint32 READ_COMMITED = DB_READ_COMMITTED;
		const static uint32 READ_UNCOMMITED = DB_READ_UNCOMMITTED;
		const static uint32 RMW = DB_RMW;
		const static uint32 IGNORE_LEASES = DB_IGNORE_LEASE;
		const static uint32 MVCC = DB_MULTIVERSION;
	};

	class DatabaseType {
	public:
		const static DBTYPE HASH = DB_HASH;
		const static DBTYPE BTREE = DB_BTREE;
		const static DBTYPE QUEUE = DB_QUEUE;
		const static DBTYPE RECNO = DB_RECNO;
		const static DBTYPE UNKNOWN = DB_UNKNOWN;
	};

	class DatabaseConfig {
		uint32 databaseFlags;
		DBTYPE databaseType;
		bool duplicates;

	public:
		static DatabaseConfig DEFAULT;

	public:
		DatabaseConfig();

		void setAllowCreate(bool allowCreate);

		void setReadOnly(bool val);

		void setDuplicates(bool val);

		/**
		 * Enclose the database open within a transaction.
		 */

		void setAutoCommit(bool transactional);

		void setThreaded(bool threaded);

		void setReadUncommited(bool value);

		void setMultiVersionConcurrencyControl(bool value);

		void setType(DBTYPE type);

		uint32 getDatabaseFlags() const;

		DBTYPE getDatabaseType() const;

		bool hasDuplicates() const;

	};

    } // namespace berkeley
  } // namespace db
} // namespace engine

using namespace engine::db::berkeley;
