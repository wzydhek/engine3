/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * CursorConfig.h
 *
 *  Created on: 15/02/2010
 *      Author: victor
 */

#pragma once

#include "system/platform.h"
#include <db.h>

namespace engine {
  namespace db {
    namespace berkeley {

	class CursorConfig {
		uint32 flags;

	public:
		static CursorConfig DEFAULT;

	public:
		CursorConfig();

		CursorConfig(uint32 flag);

		/**
		 * Specify that the cursor will be used to do bulk operations on the underlying database.
		 */

		/*void setBulkCursor(bool bulkCursor) { DB_BULK not declared?
			if (bulkCursor)
				flags |= DB_BULK;
			else
				flags &= ~DB_BULK;
		}*/

		/**
		 * Configure the cursor for read committed isolation.
		 */
		void setReadCommitted(bool readCommitted);

		/**
		 * Configure read operations performed by the cursor to return modified but not yet committed data.
		 */
		void setReadUncommitted(bool readUncommitted);

		/**
		 * Configure read operations performed by the cursor to return data as it was when the cursor opened without locking, if DatabaseConfig.setMultiversion(boolean) was configured.
		 */
		void setSnapshot(bool snapshot);

		/**
		 * Specify the Concurrent Data Store environment cursor will be used to update the database.
		 */
		void setWriteCursor(bool writeCursor);

		uint32 getFlags() const;

	};

    } // namespace berkeley
  } // namespace db
} // namespace engine

using namespace engine::db::berkeley;
