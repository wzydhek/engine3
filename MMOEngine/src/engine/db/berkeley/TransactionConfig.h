/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * TransactionConfig.h
 *
 *  Created on: 14/02/2010
 *      Author: victor
 */

#pragma once

#include <db.h>
#include "system/platform.h"

namespace engine {
  namespace db {
    namespace berkeley {

	class TransactionConfig {
		uint32 transactionFlags;

	public:
		static TransactionConfig DEFAULT;

	public:
		TransactionConfig();

		/**
		 * Configure the transaction to not write or synchronously flush the log it when commits.
		 */
		void setNoSync(bool noSync);

		/**
		 * Configure the transaction to not wait if a lock request cannot be immediately granted.
		 */
		void setNoWait(bool noWait);

		/**
		 * Configure the transaction for read committed isolation.
		 */
		void setReadCommitted(bool readCommitted);

		/**
		 * Configure read operations performed by the transaction to return modified but not yet committed data.
		 */
		void setReadUncommitted(bool readUncommitted);

		/**
		 * This transaction will execute with snapshot isolation.
		 */
		void setSnapshot(bool snapshot);

		/**
		 * Configure the transaction to write and synchronously flush the log it when commits.
		 */
		void setSync(bool sync);

		/**
        * Configure the transaction to wait if a lock request cannot be immediately granted.
        */
		void setWait(bool wait);

		/**
		 * Configure the transaction to write but not synchronously flush the log it when commits.
		 */
		void setWriteNoSync(bool writeNoSync);

		uint32 getFlags() const;
	};

    } // namespace berkeley
  } // namespace db
} // namespace engine

using namespace engine::db::berkeley;
